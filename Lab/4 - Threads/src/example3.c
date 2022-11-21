#define _XOPEN_SOURCE 700
#define NUM_THREADS 5
#define _REENTRANT

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>

void* func_thread(void* arg) {
    printf("tid:%ld> %s\n", (long)pthread_self(), (char*) arg);
    pthread_exit((void*) 0);
}

int main() {
    int i, j, status, error;
    pthread_t tid[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&(tid[i]), NULL, func_thread, "JJY") != 0) {
            printf("pthread_create\n");
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(tid[i], (void**) &status) != 0) {
            printf("pthread_join\n");
            exit(1);
        } else {
            printf("Thread %d finished with status %d\n", i, status);
        }
    }

    // error = pthread_join(tid[0], (void**) &status);
    // printf("Thread 0 finished with status %d, error %d\n", status, error);
    // error = pthread_join(tid[1], (void**) &status);
    // printf("Thread 1 finished with status %d, error %d\n", status, error);

    return EXIT_SUCCESS;
}