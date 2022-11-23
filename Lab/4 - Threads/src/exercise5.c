#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <sched.h>

#define NB_THREADS 3
#define NB_LOOPS 2

/* TODO: SYNCHRONIZATION VARIABLES */
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condIn = PTHREAD_COND_INITIALIZER;
pthread_cond_t condOut = PTHREAD_COND_INITIALIZER;
int countIn;
int canComeIn;

void wait_barrier(int n) {
    /* TODO: WAIT ON BARRIER UPON EVERY ITERATION */
    
    pthread_mutex_lock(&mx);
    if (canComeIn == 0) {
        pthread_cond_wait(&condOut, &mx);
    }
    countIn++;
    if (countIn < n) {
        pthread_cond_wait(&condIn, &mx);
    } else {
        canComeIn = 0;
        pthread_cond_broadcast(&condIn);
    }
    pthread_mutex_unlock(&mx);

    pthread_mutex_lock(&mx);
    countIn--;
    if (countIn == 0) {
        canComeIn = 1;
        pthread_cond_broadcast(&condOut);
    }
    pthread_mutex_unlock(&mx);
}


void* thread_func(void* arg) {
    int i;
    printf ("start barriers\n");
    for (i = 0; i < NB_LOOPS; i++) {
        printf ("before barrier %d\n", i);
        wait_barrier (NB_THREADS);
        printf ("after barrier %d\n", i);
    }
    pthread_exit ( (void*)0);
}


int main(int argc, char** argv) {
    
    int i;
    pthread_t tid[NB_THREADS];
    
    countIn = 0;
    canComeIn = 1;
    
    for (i = 0; i < NB_THREADS; i++)
        pthread_create((tid+i), 0, thread_func, 0);
    
    for (i = 0; i < NB_THREADS; i++)
        pthread_join(tid[i], NULL);
    
    printf("%ld> END PROG\n", pthread_self());
    
    return EXIT_SUCCESS;
    
}
