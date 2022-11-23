#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NP 3
#define NC 2
#define MAX_CAP 3
#define NVAL 10

int inside, consumed;
int stack[MAX_CAP];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_p = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_c = PTHREAD_COND_INITIALIZER;

void terminate_if_possible() {
    if (consumed == NVAL) {
        inside = -1;
        pthread_cond_broadcast(&cond_p);
        pthread_cond_broadcast(&cond_c);
        pthread_mutex_unlock(&m);
        pthread_exit((void*) 0);
    }
}

void * consumer_thread(void * args) {
    while (1) {
        pthread_mutex_lock(&m);
        
        // If empty, wait
        while (inside == 0) {
            pthread_cond_wait(&cond_p, &m);
        }

        terminate_if_possible();
        
        // start consuming
        inside--;
        printf("Consumer %ld consumes %d\n", (long) pthread_self(), stack[inside]);
        stack[inside] = 0;
        consumed++;

        // Release resource for producer
        pthread_cond_signal(&cond_c);
        
        pthread_mutex_unlock(&m);
    }
    
}


void * producer_thread(void * args) {
    while (1) {
        pthread_mutex_lock(&m);

        // If full, wait
        while (inside == MAX_CAP) {
            pthread_cond_wait(&cond_c, &m);
        }

        terminate_if_possible();

        // start producing
        stack[inside] = rand() % 100 + 1;
        inside++;
        
        // Release resource for consumer
        pthread_cond_signal(&cond_p);

        pthread_mutex_unlock(&m);
    }
    
}

int main() {
    int i, j, status;
    pthread_t tid_p[NP], tid_c[NC];

    srand(getpid());
    inside = 0;
    consumed = 0;

    for (i = 0; i < NP; i++) {
        if (pthread_create(&(tid_p[i]), NULL, producer_thread, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (i = 0; i < NC; i++) {
        if (pthread_create(&(tid_c[i]), NULL, consumer_thread, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    } 
    
    for (j = 0; j < NP; j++) {
        if (pthread_join(tid_p[j], (void**) &status) != 0) {
            perror("pthread_join");
            exit(1);
        }
        printf("Producer thread %d ended.\n", j);
    }

    for (j = 0; j < NC; j++) {
        if (pthread_join(tid_c[j], (void**) &status) != 0) {
            perror("pthread_join");
            exit(1);
        }
        printf("Consumer thread %d ended.\n", j);
    }

    return EXIT_SUCCESS;
}