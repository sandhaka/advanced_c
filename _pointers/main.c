#include <stdio.h>

int do_something(void);

typedef int do_some(void);

int main(void) {
    int** d_ptr;
    int* ptr;
    int v = 10;

    int (*ptr_do_something)(void);

    // Initialize ptr with the address of variable v. ptr now point to v.
    ptr = &v; 
    // Initialize the double pointer as pointer of pointer of v
    d_ptr = &ptr;

    // Deference the first pointer
    printf("v value via pointer: %d\n", *ptr);
    
    // Deference the double pointer
    printf("v value via duble pointer: %d\n", **d_ptr);

    // Assign a function pointer
    ptr_do_something = do_something;

    // Invoke via function pointer
    int value = (*ptr_do_something)();

    // Using typedef 
    do_some *ptr_do_some = NULL;

    ptr_do_some = &do_something;

    value = (*ptr_do_some)();
}

int do_something(void) {
    printf("I do something here!\n");
    return 3;
}