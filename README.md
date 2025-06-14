Advanced C Programming Notes
---
> Intermediate to advanced notes for C programming.
> Collected from courses and books to brush up my C know-how

### Modules and Variables
- Generally, a C file (.h and .c files) is a module.
- In a module (in a file) I can declare a local variable or a global variable. 
    - Local variables can be used inside the function where they are defined. Theay are allocated on the stack or on the heap if malloc is used explicitly. [📋](./_stack_heap_alloc/main.c)
    - Global variables can be used in any other module (declaring them as extern [📋](./_files_communication/src/))
    - If a global variable is declared with static it's valid only in the same module.
    ```C
    int number_from_function = 42;  // Global variable
    static int private_var = 88;    // It's global for the current module

    // Can be called from outise function.c using extern
    int foo() { 
        return 50;
    }

    // Cannot be called from outside function.c
    static int bar() {
        return 51;
    }
    ```
- Register keyword is used in a variable declaration (any type of data) when that variable should be stored in a register instad of RAM. When a variable is used heavily.
```C
int main(int argc, char** argv) {
    // Declare a variable directly in a CPU register
    register int regVariable = 1; // Has local liftime
    // You cannot obtain the address of a register variable of course.
    // int* reg_ptr = &regVariable; // Compile-time error
}
```
#### [Storage classes](./_storage_classes/main.c) Overview
| Storage Class | Declaration Location | Scope | Lifetime | 
| --- | --- | --- | --- |
| `auto` | Inside a function block | Within the function/block | Until the function block completes |
| `register` | Inside a function block  | Within the function/block | Until the function block completes |
| `extern` | Outside all functions  | Entire file where declared as extern | Until the program terminates |
| `static` local | Inside a function block  | Within the function/block | Until the program terminates |
| `static` global | Outside all functions  | Entire file in which it's declared | Until the program terminates |
