#include <stdio.h>

int main() {

    extern int number_from_function;    // Declare the external variable
    extern int private_var;             // Unaccessible

    printf("The number from function is: %d\n", number_from_function);
    // printf("The private_var from function is: %d\n", private_var); // Compile-time error

    return 0;
}