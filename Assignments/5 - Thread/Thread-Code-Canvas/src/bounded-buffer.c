#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NP 4
#define NC 3
#define MAX_CAP 2
#define NVAL 5

int in_production;
int consumed;
int next_i_p;
int stack[MAX_CAP];
pthread_mutex_t m_p = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_p = PTHREAD_COND_INITIALIZER;

void * consumer_thread(void * args) {
    pthread_exit((void*) 0);
}


void * producer_thread(void * args) {
    int local_next_i;

    while (1) {
        // only allow MAX_CAP producer to produce
        pthread_mutex_lock(&m_p);
        if (in_production < MAX_CAP) {
            pthread_cond_wait(&cond_p, m_p);
        } else {
            in_production++;
            local_next_i = next_i_p;
            next_i_p = (next_i_p + 1) % MAX_CAP;
        }
        pthread_mutex_unlock(&m_p);

        // produce

    }
    

    pthread_exit((void*) 0);
}

int main() {
    int i, j, status;
    pthread_t tid_p[NP], tid_c[NC];

    in_production = 0;
    consumed = 0;
    next_i_p = 0;

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