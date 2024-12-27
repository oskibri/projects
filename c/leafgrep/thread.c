#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

// Function that each thread will execute
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;  // Cast and dereference to get the thread ID
    printf("Thread %d is running\n", thread_id);
    sleep(1); // Simulate some work
    printf("Thread %d is finished\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int result;

    // Create threads in a loop
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;  // Assign each thread a unique ID to pass as argument
        result = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    // Join threads to ensure they all complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads are completed\n");
    return 0;
}

