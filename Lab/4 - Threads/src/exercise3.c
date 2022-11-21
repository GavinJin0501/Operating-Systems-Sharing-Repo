#define _XOPEN_SOURCE 700
#define N 5

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int total, finished;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * rand_thread(void *args) {
    pthread_detach(pthread_self());

    int random_val = rand() % 10;
    printf("Secondary thread %ld with random_val: %d\n", (long) pthread_self(), random_val);

    pthread_mutex_lock(&m);
    total = total + random_val;
    finished++;
    if (finished == N) {
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&m);

    pthread_exit((void*) 0);
}

void * print_therad(void *args) {
    pthread_mutex_lock(&m);
    while (finished < N) {
        pthread_cond_wait(&cond, &m);
    }
    printf("Last Secondary thread %ld print total: %d\n", (long) pthread_self(), total);
    pthread_mutex_unlock(&m);
    
    pthread_exit((void*) 0);
}

int main() {
    int i;
    pthread_t tid[N + 1];

    srand(getpid());
    total = 0;
    finished = 0;

    for (i = 0; i < N; i++) {
        if (pthread_create(&(tid[i]), NULL, rand_thread, NULL) != 0) {
            printf("pthread_create error\n");
            exit(1);
        }
    }
    if (pthread_create(&(tid[i++]), NULL, print_therad, NULL) != 0) {
        printf("pthread_create error\n");
        exit(1);
    }

    pthread_join(tid[N], NULL);
    printf("Main thread ended\n");
    return EXIT_SUCCESS;
}


