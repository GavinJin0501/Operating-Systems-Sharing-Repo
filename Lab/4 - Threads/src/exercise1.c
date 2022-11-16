#define _XOPEN_SOURCE 700
#define N 2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_control(void *args) {
    int* order = (int*) args;
    printf("Thread %d with tid (Before): %d\n", *order, (int) pthread_self());
    pthread_exit((void *) (*order * 2));
}

int main() {
    int i, status;
    int* val;
    pthread_t tid[N];

    for (i = 0; i < N; i++) {
        val = (int*) malloc(sizeof(int));
        *val = i;
        if (pthread_create(&(tid[i]), NULL, thread_control, (void*) val) != 0) {
            printf("pthread_create error\n");
            exit(1);
        }
    }

    for (i = 0; i < N; i++) {
        printf("%d:> %d\n", N, i);
        if (pthread_join(tid[i], (void**) &status) != 0) {
            printf("pthread join error\n");
            exit(1);
        } else {
            printf("Thread %d finished with status: %d\n", i, status);
        }
    }


    return EXIT_SUCCESS;
}

