# Orden

# Custom Preprocessor Directives for C++

This custom preprocessor adds several handy directives to simplify your C++ code. Below is a list of the directives and how to use them.

---

### 1. `#add standard`

**Purpose:** Adds a set of common standard C++ headers to the file.

**How to use:**
```cpp
#add standard

This directive will automatically include a predefined set of standard headers like:

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
```

### 2. `#alltogether <header1> <header2> ...`

**Purpose:** Includes multiple headers in one line.

**How to use:**
```cpp
#alltogether <iostream> <vector> <map>

Same as

#include <iostream>
#include <vector>
#include <map>

```

### 3. `#require <header>`

**Purpose:** Requires a specific header to be included in the file and saves you from running into errors if you included multiple headers that are same

**How to use:**
```cpp
#require <cmath>

Use this for including a specific header manually, ensuring no duplicates.

```

### 4. `#pb class <ClassName> {...} & pv class <ClassName> {...}`

**Purpose:** Defines a public class. The class members will be public by default or if you want private just use pv.
Please note that pv will actually place the `private:` in the begging of the class so, u can still use private and etc.

**How to use:**
```cpp
pb class MyClass {
    int x;
    void myFunction();
}

pv class MyClass {
    int x;
    void myFunction();
}


```

### 5. `#singleton class <ClassName> {...}`

**Purpose** Defines a singleton class. This pattern restricts the instantiation of a class to one object.

**How to use:**
```cpp
singleton class Singleton {
    int x;
    void someMethod();
}


This will expand into:


class Singleton {
private:
    Singleton() = default;
    static Singleton instance;
public:
    static Singleton& getInstance() {
        return instance;
    }
    int x;
    void someMethod();
};


```

### 6. `#for_range (var, start, end)`

**Purpose** Expands to a for loop that iterates from start to end. Very simple, but can be just clear and simple. without other hassle

**How to use:**
```cpp
for_range (i, 0, 10) {
    std::cout << i << "\n";
}

```

### 7. `#log <message>`

**Purpose** debugging, tests. Used when you need to output checks and etc for flow control. 

**How to use:**
```cpp
#log "Successed! Continue >>> "

```

### How this works?

The whole logic is something similar to macros in C++ natively. We litarally process the code BEFORE compiling it or anything else, Orden just simplifies this and also adds handy simple template init and a compiling program that will manage the code.

> [!CAUTION]
> please write your code and create files only in src folder and dont interact with build folder. It can break the program.
> YOU MUST CREATE THE TEMPLATE
> 
> GCC and C++ must be already installed on your system, for this follow offcial guides.

### Installation 

COMING SOON...

For now run in terminal

`gh repo clone IvanKoskov/Orden`

or 

clone using this link

`https://github.com/IvanKoskov/Orden.git`

also you can just dowload zip of the project and explore

`https://github.com/IvanKoskov/Orden/archive/refs/heads/main.zip`
> [!TIP]
> or as an easy way use use our script as you cloned the repo
>
> Run the following in the folder of project (Orden):
>
> 1. `chmod +x proj_build.sh` 
> 2. `./proj_build.sh`
> 3. After this wait as it will compile and setup everything!
> 4. If you are promted for the root password or other passwords just type them in (can be different on different systems).








