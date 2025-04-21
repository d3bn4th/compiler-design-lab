When you use `g++ -c` or `g++` without the `-S` flag, **the output is NOT assembly code**—it is actual **machine code**, i.e., the binary instructions the CPU can execute (stored in an object file `.o` or an executable). These files, however, are not human-readable (they’re in binary format).

### **Clarification of Command Outputs**
| Command                  | Output file       | Content                       |
|--------------------------|------------------|-------------------------------|
| `g++ -S example.cpp`     | `example.s`      | Human-readable assembly code  |
| `g++ -c example.cpp`     | `example.o`      | Machine code (object file, binary) |
| `g++ example.cpp -o exe` | `exe`            | Full executable (machine code, binary) |

---

## **Inspecting the Machine Code**

If you open `example.o` or `exe` in a text editor, you will see gibberish, because those are **binary (machine code) files**.

To **view the machine code (as hex bytes)** for educational purposes, you can use tools like:
- `hexdump -C example.o`
- `xxd example.o`
- `objdump -d example.o` (shows addresses, hex bytes, and disassembled instructions)

---

## **Summary: What You Need To Do**

Let's walk through the process again:

### 1. Write your C++ code:
```cpp
// main.cpp
int main() {
    int a = 5 + 3;
    return a;
}
```

### 2. Compile to Machine Code (Object File):
```bash
g++ -c main.cpp -o main.o
```
- `main.o` is a **machine code** (object) file.

### 3. (Optional) Compile to Executable:
```bash
g++ main.cpp -o main_exe
```
- `main_exe` is a **machine code** (executable) file.

### 4. To **see the bytes** (for educational purposes):

```bash
hexdump -C main.o | head
```
or
```bash
xxd main.o | head
```

You will see output like:
```
00000000  7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00  |.ELF............|
...
```

This *is* machine code (including ELF headers, section info, etc).

---

## **Automated C++ Program Example**

If you want a **C++ program that generates the machine code file**:

```cpp
#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
    // Write C++ program to file
    std::ofstream code("userprog.cpp");
    code << "int main() { int a = 5 + 3; return a; }";
    code.close();

    // Compile to machine code (object file)
    if(system("g++ -c userprog.cpp -o userprog.o") != 0) {
        std::cerr << "Compilation failed!\n";
        return 1;
    }
    std::cout << "Machine code generated and stored in userprog.o\n";

    // Optional: To create executable
    // system("g++ userprog.cpp -o userprog_exe");

    return 0;
}
```
Compile and run this.  
Open `userprog.o` with a hex editor to see the raw machine code.

---

## **In Summary**

- `g++ -c file.cpp -o file.o` produces **machine code** in `file.o`.
- If you see assembly code, you are using the `-S` flag, which you should omit.

**You do not need an extra step to "convert assembly to machine code"—the compiler does this for you!**  
If you want the raw bytes, inspect the `.o` or executable with `hexdump` or `xxd`.

---

If you have a specific C++ code and want to see the hex bytes or specific machine instructions for a portion, let me know!

Sources

