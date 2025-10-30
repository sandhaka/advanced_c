#include <pthread.h>
#include <stdio.h>
#include <mm_malloc.h>

// Just to avoid warning on printf arguments:
#include <inttypes.h>   // PRIuPTR
#include <stdint.h>     // uintptr_t

void *fn(void *arg) {
    pthread_t id = pthread_self();
    pthread_t *thread_id;

    printf("Hello from thread %" PRIuPTR ".\n", (uintptr_t) id);
    
    thread_id = (pthread_t *) malloc(sizeof(pthread_t));
    *thread_id = id;

    // Equivalent to: return thread_id in this case
    pthread_exit(thread_id);
}

int main(int argc, char** argv) {
    pthread_t thread_local;
    void* retval;

    // Create and start a thread exuting the function
    pthread_create(&thread_local, NULL, fn, NULL);
    
    // Wait thread to finish
    pthread_join(thread_local, &retval);

    printf("Called thread: %" PRIuPTR " returned.\n", *((uintptr_t *) retval));

    // Exit current thread
    free(retval);
    
    return 0;
}
