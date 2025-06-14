int main(int argc, char** argv) {
    // Declare a variable directly in a CPU register
    register int regVariable = 1; // Has local liftime
    // You cannot obtain the address of a register variable of course.
    // int* reg_ptr = &regVariable; // Compile-time error
    
}