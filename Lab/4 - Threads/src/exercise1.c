#define _XOPEN_SOURCE 700
#define N 5

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int* val;

void *thread_control(void *args) {
    int order = * (int*) args;
    printf("Thread %d with tid (Before): %ld\n", order, (long) pthread_self());
    pthread_exit((void*) (intptr_t) (order * 2));
}

int main() {
    int i, j, status;
    
    pthread_t tid[N];

    for (i = 0; i < N; i++) {
        val = (int*) malloc(sizeof(int));
        *val = i;
        if (pthread_create(&(tid[i]), NULL, thread_control, (void*) val) != 0) {
            printf("pthread_create error\n");
            exit(1);
        }
    }

    for (j = 0; j < N; j++) {
        if (pthread_join(tid[j], (void**) &status) != 0) {
            printf("pthread join error\n");
            exit(1);
        } else {
            printf("Thread %d finished with status: %d\n", j, status);
        }
    }

    return EXIT_SUCCESS;
}

