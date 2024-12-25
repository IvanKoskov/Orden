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
