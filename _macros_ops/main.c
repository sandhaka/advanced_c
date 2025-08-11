#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Using macros to speed up a sort algorithm
*/

#define SWAP_M(a, p1, p2) \
    int t = a[p1]; \
    a[p1] = a[p2]; \
    a[p2] = t;

inline static void usage(const char* pr) {
    printf("Sorting array of int, usage:\n");
    printf("%s 2 7 1 10 4 1\n", pr);
    printf("1 1 2 4 7 10\n");
}

inline static void show(const int * const numbrs, size_t length) {
    for (int i = 0; i < length; i++) printf("%d ", numbrs[i]);
    printf("\n");
}

static int partition(int * const restrict numbrs, int lo, int hi) {
    int pivot = numbrs[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (numbrs[j] <= pivot) {
            i++;
            SWAP_M(numbrs, i, j);
        }
    }
    i++;
    SWAP_M(numbrs, i, hi);
    return i;
}

static void sort(int * const restrict numbrs, int lo, int hi) {
    if (lo >= hi || lo < 0)
        return;
    int p = partition(numbrs, lo, hi);
    sort(numbrs, lo, p - 1);
    sort(numbrs, p + 1, hi);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No arguments found!\n");
        usage(argv[0]);
    }

    int in[argc - 1];
    for (int i = 1; i < argc; i++) {
        int in_number = atoi(argv[i]);
        printf("%d was read\n", in_number);
        in[i - 1] = in_number;
    }

    int length = argc - 1;
    int hi = length - 1;

    printf("Your input: \n");
    show(in, length);
    clock_t start = clock();
    sort(in, 0, hi);
    clock_t end = clock();
    double elapsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Sorted: \n");
    show(in, length);
    printf("Sort execution time: %.3f ms\n", elapsed);
}
