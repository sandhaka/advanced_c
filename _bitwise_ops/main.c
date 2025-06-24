#include <stdio.h>
#include <mm_malloc.h>

/* 
    Include common.c:
    gcc -pedantic main.c ../_common/bin_2_short.c 
 */

extern int short_to_bin_str(short d, char* buffer, size_t lenght);
extern short bin_str_to_short(const char binary[]);

static void free_buffer(char** pointers, size_t count) {
    for (int i = 0; i < count; i++) {
        free(pointers[i]);
    }
}

int main(int argc, char** argv) {

    short int w1 = 167;
    short int w2 = 61;
    short int success, r = 0;
    short int buflen = 16 + 1;

    char* w1b = (char *) malloc(sizeof(char) * buflen);
    char* w2b = (char *) malloc(sizeof(char) * buflen);
    char* res = (char *) malloc(sizeof(char) * buflen);

    char* mem_resources[] = { w1b, w2b, res };

    if (argc > 2) {
        printf("Reading w1 from input: %s\n", argv[1]);   
        printf("Reading w2 from input: %s\n", argv[2]);     
        w1 = atoi(argv[1]);
        w2 = atoi(argv[2]);
    }

    success = short_to_bin_str(w1, w1b, buflen);
    if (success < 0) {
        free_buffer(mem_resources, 3);
        return -1;
    }
    printf("w1: %d, (%s)\n", w1, w1b);
    success = short_to_bin_str(w2, w2b, buflen);
    if (success < 0) {
        free_buffer(mem_resources, 3);
        return -1;
    }
    printf("w2: %d, (%s)\n", w2, w2b);

    r = w1 & w2;
    printf("w1 & w2: %d\n", r);
    printf("%s\n", w1b);
    printf("%s\n", w2b);
    printf("---\n");
    success = short_to_bin_str(r, res, buflen);
    if (success < 0) {
        free_buffer(mem_resources, 3);
        return -1;
    }
    printf("%s (%d)\n\n\n", res, bin_str_to_short(res));    

    r = w1 | w2;
    printf("w1 | w2: %d\n", r);
    printf("%s\n", w1b);
    printf("%s\n", w2b);
    printf("---\n");
    success = short_to_bin_str(r, res, buflen);
    if (success < 0) {
        free_buffer(mem_resources, 3);
        return -1;
    }
    printf("%s (%d)\n\n\n", res, bin_str_to_short(res));        

    r = w1 ^ w2;
    printf("w1 ^ w2: %d\n", r);
    printf("%s\n", w1b);
    printf("%s\n", w2b);
    printf("---\n");
    success = short_to_bin_str(r, res, buflen);
    if (success < 0) {
        free_buffer(mem_resources, 3);
        return -1;
    }
    printf("%s (%d)\n\n\n", res, bin_str_to_short(res)); 
    
    r = ~w1 + 1;
    printf("~w1: %d\n", r);
    printf("%s\n", w1b);
    printf("---\n");
    success = short_to_bin_str(r, res, buflen);
    if (success < 0) {
        free_buffer(mem_resources, 3);
        return -1;
    }
    printf("%s (%d)\n\n\n", res, bin_str_to_short(res)); 

    free_buffer(mem_resources, 3);

    return 0;
}
