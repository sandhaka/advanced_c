#include <pthread.h>
#include <stdio.h>
#include <mm_malloc.h>

void *fn(void *arg) {
    pthread_t id = pthread_self();
    printf("Hello from thread %d.\n", (int) id);
    int *thread_id;
    thread_id = (int *) malloc(sizeof(int));
    *thread_id = (int) id;
    pthread_exit(thread_id);
}

int main(int argc, char** argv) {
    pthread_t thread_local;
    void* retval;

    // Create and start a thread exuting the function
    pthread_create(&thread_local, NULL, fn, NULL);
    
    // Wait thread to finish
    pthread_join(thread_local, &retval);

    printf("Called thread: %d returned.\n", *((int *) retval));

    // Exit current thread
    free(retval);
    
    return 0;
}
