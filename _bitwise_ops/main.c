#include <stdio.h>
#include <mm_malloc.h>

/* 
    Include common.c:
    gcc -pedantic main.c ../_common/bin_2_short.c 
 */

extern char* shortToBinStr(short d);
extern short binStrToShort(const char binary[]);

int main(int argc, char** argv) {

    short int w1 = 167;
    short int w2 = 61;
    short int r = 0;
    char* res;

    if (argc > 1) {
        printf("Reading w1 from input: %s\n", argv[1]);   
        printf("Reading w2 from input: %s\n", argv[2]);     
        w1 = atoi(argv[1]);
        w2 = atoi(argv[2]);
    }

    char* w1b = shortToBinStr(w1);
    if (w1b == NULL) return -1;
    printf("w1: %d, (%s)\n", w1, w1b);
    
    char* w2b = shortToBinStr(w2);
    if (w2b == NULL) return -1;
    printf("w2: %d, (%s)\n", w2, w2b);

    r = w1 & w2;
    printf("w1 & w2: %d\n", r);
    printf("%s\n", w1b);
    printf("%s\n", w2b);
    printf("---\n");
    res = shortToBinStr(r);
    if (res == NULL) return -1;
    printf("%s (%d)\n\n\n", res, binStrToShort(res));    

    r = w1 | w2;
    printf("w1 | w2: %d\n", r);
    printf("%s\n", w1b);
    printf("%s\n", w2b);
    printf("---\n");
    res = shortToBinStr(r);
    if (res == NULL) return -1;
    printf("%s (%d)\n\n\n", res, binStrToShort(res));        

    r = w1 ^ w2;
    printf("w1 ^ w2: %d\n", r);
    printf("%s\n", w1b);
    printf("%s\n", w2b);
    printf("---\n");
    res = shortToBinStr(r);
    if (res == NULL) return -1;
    printf("%s (%d)\n\n\n", res, binStrToShort(res)); 
    
    r = ~w1 + 1;
    printf("~w1: %d\n", r);
    printf("%s\n", w1b);
    printf("---\n");
    res = shortToBinStr(r);
    if (res == NULL) return -1;
    printf("%s (%d)\n\n\n", res, binStrToShort(res)); 

    free(w1b);
    free(w2b);
    free(res);

    return 0;
}
