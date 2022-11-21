#define _XOPEN_SOURCE 700
#define N 5

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int total;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void * rand_thread(void *args) {
    int random_val = rand() % 10;
    printf("Secondary thread rand %ld> %d\n", (long) pthread_self(), random_val);

    pthread_mutex_lock(&m);
    total = total + random_val;
    pthread_mutex_unlock(&m);
    
    pthread_exit((void*) 0);

}

int main() {
    int i, j, status;
    pthread_t tid[N];

    srand(getpid());
    total = 0;

    for (i = 0; i < N; i++) {
        if (pthread_create(&(tid[i]), NULL, rand_thread, NULL) != 0) {
            printf("pthread_create error\n");
            exit(1);
        }
    }

    for (j = 0; j < N; j++) {
        if (pthread_join(tid[j], (void**) &status) != 0) {
            printf("pthread join error\n");
            exit(1);
        }
    }
    
    printf("Main thread ended with total: %d\n", total);
    return EXIT_SUCCESS;
}


