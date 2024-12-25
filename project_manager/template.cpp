#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

void createFile(const std::string &path, const std::string &content = "") {
    std::ofstream file(path);
    if (file.is_open()) {
        file << content;
        file.close();
        std::cout << "Created: " << path << "\n";
    } else {
        std::cerr << "Failed to create: " << path << "\n";
    }
}

void createOrdProject(const std::string &projectName) {
    // Base folder
    std::filesystem::path projectPath = projectName;
    if (std::filesystem::exists(projectPath)) {
        std::cerr << "Project already exists: " << projectName << "\n";
        return;
    }

    // Create directories
    std::filesystem::create_directories(projectPath / "src");
    std::filesystem::create_directories(projectPath / "include");
    std::filesystem::create_directories(projectPath / "build");

    // Create main .ord file
    std::string mainFilePath = (projectPath / "src" / "main.ord").string();
    createFile(mainFilePath, 
        "#add standard\n"
        "#alltogether <iostream>\n\n"
        "int main() {\n"
        "    printf(\"Hello, World!\\n\");\n"
        "    return 0;\n"
        "}\n"
    );

    // Create example header file
    std::string headerFilePath = (projectPath / "include" / "example.h").string();
    createFile(headerFilePath, 
        "#ifndef EXAMPLE_H\n"
        "#define EXAMPLE_H\n\n"
        "void exampleFunction();\n\n"
        "#endif // EXAMPLE_H\n"
    );

    // Create README
    std::string readmeFilePath = (projectPath / "README.md").string();
    createFile(readmeFilePath, 
        "# " + projectName + "\n\n"
        "This is a sample project using `.ord` files with a custom preprocessor.\n"
    );

    // Create build script
    std::string buildFilePath = (projectPath / "build.sh").string();
    createFile(buildFilePath, 
        "#!/bin/bash\n"
        "set -e\n\n"
        "// Replace this with the actual preprocessor command\n"
        "preprocessor src/main.ord build/main.cpp\n\n"
        "g++ build/main.cpp -o build/" + projectName + "\n\n"
        "echo \"Build complete! Run ./build/" + projectName + " to execute.\"\n"
    );
    std::filesystem::permissions(buildFilePath, std::filesystem::perms::owner_exec, std::filesystem::perm_options::add);

    std::cout << "Project setup complete: " << projectName << "\n";
}

int main() {
    std::string projectName;

    // Loop until a valid project name is entered
    do {
        std::cout << "Enter the project name: ";
        std::getline(std::cin, projectName);

        // Trim whitespace and check if the name is valid
        projectName.erase(0, projectName.find_first_not_of(" \t")); // Trim leading spaces
        projectName.erase(projectName.find_last_not_of(" \t") + 1); // Trim trailing spaces

        if (projectName.empty()) {
            std::cout << "Project name cannot be empty. Please try again.\n";
        }
    } while (projectName.empty());

    createOrdProject(projectName);

    return 0;
}
