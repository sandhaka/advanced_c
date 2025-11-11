#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_attr_t attr;

void *do_work(void *thread_id) {
    long tid;
    size_t stack_size;

    tid = (long) thread_id;
    pthread_attr_getstacksize(&attr, &stack_size);

    printf("Thread %ld: stack size = %li bytes \n", tid, stack_size);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t thread_local;
    long t = 0;

    // Initialize the global variable before calling pthread_attr_* functions
    pthread_attr_init(&attr);

    pthread_create(&thread_local, &attr, &do_work, (void *)t);

    pthread_join(thread_local, NULL);

    printf("Main terminate after thread join\n");

    return 0;
}
