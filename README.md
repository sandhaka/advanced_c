Advanced C Programming Notes
---
> Intermediate to advanced notes for C programming.
> Collected from courses and books to brush up my C know-how. 
> The topics noted is a personal choice.

### Modules and Variables
- Generally, a C file (.h and .c files) is a module.
- In a module (in a file) I can declare a local variable or a global variable. 
    - Local variables can be used inside the function where they are defined. Theay are allocated on the stack or on the heap if malloc is used explicitly. [📋](./_stack_heap_alloc/main.c)
    - Global variables can be used in any other module (declaring them as extern [📋](./_files_communication/src/))
    - If a global variable is declared with `static` it's valid only in the same module.
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
- `Register` keyword is used in a variable declaration (any type of data) when that variable should be stored in a register instad of RAM. When a variable is used heavily.
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
### Advanced Data Types
- `#define` preprocessor directive can be used to define symbolic, or manifest, constants in a program. Is limited to one line length (but backslash/newline can be used to spread on multiple physical lines). Executed before the compilation. It's literally a substitution before compilation.
- Primary use of the `#define` preprocessor is to assign a symbolic name: `#define YES 1` or `#define PI 3.14`
- `typedef` keyword enables to create an own name for an existing data type: `typedef in Counter` define a counter variable of type `int`.
```C
typedef char* char_ptr;
char_ptr p;     // char* p;
char_ptr a, *b  // char *a, **b;
```
- In general, `typedef` is useful to keep the programs simple and easy to work with and improve code portability. As example, when working on size: The size of int may vary across platforms. `typedef` can be used to abstract the underlying type:
```C
// types.h
#ifndef _SIZE_T
#define _SIZE_T
#include <machine/_types.h> /* __darwin_size_t */
typedef __darwin_size_t        size_t;
#endif  /* _SIZE_T */
```
```C
// main.c
size_t size;
```
- On the current machine, a Mac, `size_t` is a defined type exactly as showed: `typedef __darwin_size_t        size_t;` in system headers. This is a real example of `typedef` feature usage for portability.
> About array's length: Variable length array should be avoided. Use pointers and `malloc` and `realloc` instead.
- Flexible array members (FAMs) in C are a feature for defining structs with a variable-sized array at the end, typically used in low-level systems programming, memory management, or serialization.
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pkt {
    size_t length;
    char data[];    // Flexible array member declared as the latest item of the struct with [].
};

int main(void) {

    printf("Flexible array members are supported from C99 standard. This program is compiled using: %ld\n", __STDC_VERSION__); 

    const char* msg = "Welcome message!";
    size_t msg_length = strlen(msg) + 1;
    struct pkt* packet_ptr = malloc(sizeof(struct pkt) + msg_length);

    packet_ptr->length = msg_length;
    memcpy(packet_ptr->data, msg, msg_length);

    printf("Payload: %s\n", packet_ptr->data);

    return 0;
}
```
- Designed initializers help to declare an array of elements with predefined value. Is pretty simple: `struct point {int x, y;};`. `struct point pts[5] = { [2].y = 5,  [2].x = 6}`. Initialize only the third element of the array.
### Type Qualifiers
- The `const` keyword is widely used in applications. Not only for constant value delcarations.
    - `const float *pf;` Is a pointer to constant float value. The value cannot change.
    - `float * const pt;` Is a constant pointer to a float variable. The pointer cannot change but the value can.
    - `const float * const ptr;` Both are constants.
    - `float const *pfc;` The same of `const float *pfc` but the pointer cannot be used to change the value.
- Here the position of the `*` is crucial
- On parameters
    - Here `void display(const int array[], int limit)` the first parameter is an array of constant elements, these cannot be changed.
    - As the following: `char *strcat(char *restrict s1,  const char * restrict s2);` The second parameter is not going to change.
- Another typical usage of `const` is in the global variables. To ensure to create a single constant copy of a variable: `static const char A = 'A';`.
- `volatile` is particularly used in embedded software for memory-mapped peripheral registers or global variables accessed by multiple tasks within a multi-threaded application. He force the compiler to not optimise a variable usage and to not use any caching with it but to obtain the most updated value of it. A variable should be declared as volatile whenever its value could change unexpectedly. Probably will be much more clear in the multi-threaded related chapter.
- A pointer can be `volatile`, and there are different ways to declare a volatile pointer depending on what exactly needs to be volatile.
    - Volatile Pointer to Non-Volatile Data
    ```c
    int data = 42;
    int *volatile ptr = &data;  // The pointer itself is volatile
    ```
    Here, the pointer's address can change unexpectedly, but the data it points to is normal.
    - Non-Volatile Pointer to Volatile Data
    ```c
    volatile int status_register;
    volatile int *ptr = &status_register;  // Points to volatile data
    ```
    Here, the data being pointed to can change unexpectedly, but the pointer itself is normal.
    - Volatile Pointer to Volatile Data
    ```c
    volatile int status_register;
    volatile int *volatile ptr = &status_register;  // Both pointer and data are volatile
    ```
    Both the pointer's address and the data it points to can change unexpectedly.

- Here's a practical example showing these concepts:
````c
#include <stdio.h>

void hardware_monitor(void) {
    // Memory-mapped hardware register (volatile data)
    volatile int *status = (volatile int *)0x20000000;
    
    // Pointer that can be modified by an interrupt routine
    int *volatile interrupt_ptr;
    
    // Both pointer and data can change unexpectedly
    volatile int *volatile dual_volatile_ptr;
    
    // Reading from volatile memory
    int value = *status;  // Will always read from memory, not cached
}
````
- The key rule is: use `volatile` when the value (either the pointer or what it points to) can change in ways the compiler can't predict through normal program flow.
- A parameter can be both `const` and `volatile`. This combination is particularly useful when dealing with hardware registers that shouldn't be modified by the software but can change due to hardware events.
```c
#include <stdio.h>

// Function that reads from a hardware status register
void check_status(volatile const int* status_register) {
    // Can read but not modify the register
    // Will always read from memory due to volatile
    // Will not cache the value due to volatile
    if (*status_register & 0x1) {
        printf("Status bit 0 is set\n");
    }
}

int main(void) {
    // ...existing code...

    // Example with both const and volatile
    volatile const int hardware_status = 0x1;  // Simulating a read-only hardware register
    check_status(&hardware_status);

    return 0;
}
```
- `restrict` is a another optimization oriented keyword, introduced by the C99 standard, that can be used in pointer declarations. By adding this type qualifier, a programmer hints to the compiler that for the lifetime of the pointer, no other pointer will be used to access the object to which it points. Without the restrict, the compiler has to assume the worse case that some other identifier might have changed the data in between two uses of a pointer. it's a promise from the programmer to the compiler. Breaking this promise leads to undefined behavior
- The following would be incorrect usage:
  ```c
  void vector_add(double * restrict result, 
                const double * restrict v1, 
                const double * restrict v2, 
                int size);

  double arr[] = {1.0, 2.0, 3.0, 4.0};
  vector_add(arr, arr, arr, 4);  // Wrong! Pointers overlap
  ```
- All these features still rely on the developer responsability but produce effective more optimized code when used correctly!
- Let's see a comprensive example here [📋](./_t_qualifiers/main.c)
### Bit Manipulation
- Bit manipulation techniques can be used to solve various conversion problems, often leading to more efficient solutions compared to traditional arithmetic methods. Classical conversion problems leveraging bit manipulation [📋](./_common/bin_2_short.c).
- Bit operations can be performed on any type of integer value and characters, but cannot be performed on floating-poit values.
- Bitwise operations with a mask are usually used to store multiple information in a variable (each bit corresponds to a setting).