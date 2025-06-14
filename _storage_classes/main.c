// An int variable with block scope temporary storage
void foo(void) {
    int a = 0;
}

// A global double variable that is only accessible inside this file
static double h = 2.4;

// A global float variable that is accessible within the entire program
float k = 5.6;

// A float local variable with permanent storage
void bar(void) {
    static float j = 5.7;
}

// A register int variable
void reg(void) {
    register int i = 6;
}

// A function that is only accessible with the file it is defined
static void private_function(void) {

}

int main(void) {  }
