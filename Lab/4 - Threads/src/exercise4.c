#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <sched.h>

#define NB_THREADS 4


/* TODO: global variables */


void wait_barrier(int n) {
    /* TODO: synchronization */
}


void* thread_func(void* arg) {
    printf ("afore barrier\n");
    wait_barrier (NB_THREADS);
    printf ("after barrier\n");
    pthread_exit ( (void*)0);
}


int main(int argc, char** argv) {
    
    int i;
    pthread_t tid[NB_THREADS];
    
    /* initialize global variables */
    
    for (i = 0; i < NB_THREADS; i++)
        pthread_create((tid+i), 0, thread_func, 0);
    
    for (i = 0; i < NB_THREADS; i++)
        pthread_join(tid[i], NULL);
    
    printf("%ld> END PROG\n", pthread_self());
    
    return EXIT_SUCCESS;
    
}
