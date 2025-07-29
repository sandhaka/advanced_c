#include<stdio.h>

union Data {
    int i;
    float f;
    char str[16]; // Largest member
} data;

int main()
{
    printf("The size of the Data union is: %d\n", sizeof(data));
    return 0;
}
