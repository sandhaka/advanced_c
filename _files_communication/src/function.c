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