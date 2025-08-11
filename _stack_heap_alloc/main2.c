#include <stdlib.h>
#include <stdio.h>

void allocate_32(int** array) {
    *array = (int*) malloc(sizeof(int) * 32);
}

int main(void) {
    int* array = NULL;
        
    printf("Array address: %p\n", (void*)array);

    allocate_32(&array);

    printf("Array address: %p\n", (void*)array);
}
