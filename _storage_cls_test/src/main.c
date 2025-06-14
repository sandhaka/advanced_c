#include <stdio.h>

int main(int argc, char** argv) {

    printf("Using argc: %d\n", argc);
    printf("Using argv:\n");

    for (int i = 0; i < argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);

    return 0;
}
