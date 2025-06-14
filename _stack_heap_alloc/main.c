#include <stdio.h>
#include <stdlib.h>

void using_stack(void)
{
    int age = 38;
    double salary = 123456.78;
    double list[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    printf("Using stack to allocate variables like Age: %d\n", age);
}

void using_heap(void)
{
    int *age = (int *)malloc(sizeof(int));
    double *salary = (double *)malloc(sizeof(double));
    double *list = (double *)malloc(5 * sizeof(double));

    if (age != NULL && salary != NULL && list != NULL) {
        *age = 38;
        *salary = 123456.78;
        for (int i = 0; i < 5; i++) {
            list[i] = (i + 1) * 1.1;
        }
    }

    printf("Using heap to allocate variables like Age: %d\n", *age);
    
    // Free allocated memory
    free(age);
    free(salary);
    free(list);
}

int main(void)
{
    using_stack();
    using_heap();
    return 0;
}
