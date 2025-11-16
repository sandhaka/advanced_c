#include <stdio.h>
#include <string.h>

int main(void) {
    char first[7] = "ABCDEF\0";
    char second[7] = "defghi\0";
    int i = 5;
    int j = 6;

    int t = i + j++;

    char* p = first;
    char* s = second;

    *p++ = *s++;
    
    printf("%s\n", p);
    printf("%s\n", s);
    printf("%d\n", t);

    return 0;
}