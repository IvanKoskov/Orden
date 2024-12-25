#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <filesystem>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

class Preprocessor {
public:
void processOrdFile(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream inputFile(inputPath);
    std::ofstream outputFile(outputPath);
    std::unordered_set<std::string> includedHeaders;

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Handle standard header addition
        if (line.find("#add standard") == 0) {
            std::vector<std::string> standardHeaders = {
                "<iostream>", "<vector>", "<string>",
                "<algorithm>", "<map>", "<set>"
            };

            for (const auto &header : standardHeaders) {
                if (includedHeaders.insert(header).second) {
                    outputFile << "#include " << header << "\n";
                }
            }
        } 
        // Handle multiple includes
        else if (line.find("#alltogether") == 0) {
            size_t start = line.find(' ') + 1;
            std::string headers = line.substr(start);
            std::stringstream ss(headers);
            std::string header;

            while (ss >> header) {
                if (includedHeaders.insert(header).second) {
                    outputFile << "#include " << header << "\n";
                }
            }
        } 
        // Handle #require <header>
        else if (line.find("#require") == 0) {
            size_t start = line.find('<');
            size_t end = line.find('>');
            std::string header = line.substr(start, end - start + 1);

            if (includedHeaders.insert(header).second) {
                outputFile << "#include " << header << "\n";
            }
        } 
       else if (line.find("#log") == 0) {
    size_t start = line.find(' ') + 1;
    std::string message = line.substr(start);

    // Trim leading and trailing spaces
    message.erase(0, message.find_first_not_of(" \t"));
    message.erase(message.find_last_not_of(" \t") + 1);

    // Correctly escape double quotes inside the message
    std::string correctedMessage = message;
    size_t pos = 0;
    while ((pos = correctedMessage.find("\"", pos)) != std::string::npos) {
        correctedMessage.insert(pos, "\\");
        pos += 2; // Skip over the inserted escape character
    }

    outputFile << "std::cout << \"[LOG]: " << correctedMessage << "\" << std::endl;\n";
    }


        // Handle pb class {...}
        else if (line.find("pb class") == 0) {
            std::regex pbClassRegex(R"(pb\s+class\s*(\w*)\s*\{)");
            std::smatch match;
            if (std::regex_search(line, match, pbClassRegex)) {
                std::string className = match[1];
                outputFile << "class " << className << " {\npublic:\n";
            } else {
                outputFile << line << "\n";
            }
        } 
        // Handle pv class {...}
        else if (line.find("pv class") == 0) {
            std::regex pvClassRegex(R"(pv\s+class\s*(\w*)\s*\{)");
            std::smatch match;
            if (std::regex_search(line, match, pvClassRegex)) {
                std::string className = match[1];
                outputFile << "class " << className << " {\nprivate:\n";
            } else {
                outputFile << line << "\n";
            }
        } 
        // Handle singleton class {...}
        else if (line.find("singleton class") == 0) {
            std::regex singletonClassRegex(R"(singleton\s+class\s*(\w*)\s*\{)");
            std::smatch match;
            if (std::regex_search(line, match, singletonClassRegex)) {
                std::string className = match[1];
                outputFile << "class " << className << " {\nprivate:\n"
                           << "    " << className << "() = default;\n"
                           << "    static " << className << " instance;\n"
                           << "public:\n"
                           << "    static " << className << "& getInstance() {\n"
                           << "        return instance;\n"
                           << "    }\n";
            } else {
                outputFile << line << "\n";
            }
        } 
        // Handle for_range (var, start, end)
        else if (line.find("for_range") == 0) {
            size_t start = line.find('(') + 1;
            size_t end = line.find(')');
            std::string args = line.substr(start, end - start);

            std::stringstream ss(args);
            std::string var, startValue, endValue;
            std::getline(ss, var, ',');
            std::getline(ss, startValue, ',');
            std::getline(ss, endValue, ',');

            // Trim whitespace
            var.erase(0, var.find_first_not_of(" \t"));
            var.erase(var.find_last_not_of(" \t") + 1);
            startValue.erase(0, startValue.find_first_not_of(" \t"));
            startValue.erase(startValue.find_last_not_of(" \t") + 1);
            endValue.erase(0, endValue.find_first_not_of(" \t"));
            endValue.erase(endValue.find_last_not_of(" \t") + 1);

            outputFile << "for (int " << var << " = " << startValue << "; "
                       << var << " < " << endValue << "; ++" << var << ") {\n";
        } 
        // Handle end of classes or blocks
        else if (line.find("};") != std::string::npos) {
            outputFile << "};\n";
        } 
        // Copy other lines as-is
        else {
            outputFile << line << "\n";
        }
    }

    inputFile.close();
    outputFile.close();
}



    void cleanBuildFolder(const fs::path &buildFolder) {
        if (fs::exists(buildFolder)) {
            for (const auto &entry : fs::directory_iterator(buildFolder)) {
                fs::remove(entry.path());
            }
        }
    }

    void processProject(const std::string &projectPath) {
        fs::path srcFolder = fs::path(projectPath) / "src";
        fs::path buildFolder = fs::path(projectPath) / "build";

        if (!fs::exists(buildFolder)) {
            fs::create_directory(buildFolder);
        }

        cleanBuildFolder(buildFolder);

        for (const auto &entry : fs::directory_iterator(srcFolder)) {
            if (entry.is_regular_file() && entry.path().extension() == ".ord") {
                std::string inputPath = entry.path().string();
                fs::path outputPath = buildFolder / entry.path().filename();
                outputPath.replace_extension(".cpp");
                processOrdFile(inputPath, outputPath.string());
                std::cout << "Processed: " << inputPath << " -> " << outputPath.string() << "\n";
            }
        }
    }

    bool buildExecutable(const fs::path &buildFolder, const std::string &executableName) {
        std::string command = "g++ -std=c++17 " + buildFolder.string() + "/*.cpp -o " + executableName;
        int result = system(command.c_str());
        return result == 0;
    }

    void cleanGeneratedFiles(const fs::path &buildFolder) {
        for (const auto &entry : fs::directory_iterator(buildFolder)) {
            if (entry.path().extension() == ".cpp") {
                fs::remove(entry.path());
            }
        }
    }
};

int main() {
    Preprocessor preprocessor;
    std::string projectPath;
    std::cout << "Enter the project path: ";
    std::getline(std::cin, projectPath);

    fs::path buildFolder = fs::path(projectPath) / "build";
    std::string executableName = "output";

    preprocessor.processProject(projectPath);

    if (preprocessor.buildExecutable(buildFolder, executableName)) {
        std::cout << "Build successful. Executable created: " << executableName << "\n";
        preprocessor.cleanGeneratedFiles(buildFolder);
        std::cout << "Temporary files cleaned.\n";
    } else {
        std::cerr << "Build failed. Please check for errors.\n";
    }

    return 0;
}




//  /Users/evan/OrdTesting