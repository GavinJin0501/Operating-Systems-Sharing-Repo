#define _XOPEN_SOURCE 700
#define NUM_THREADS 5

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>

void* func(void* args) {
    printf("%d\n", * (int*) args);
    return NULL;
}

int main() {
    int *pt_ind;
    int i;
    pthread_t tid[NUM_THREADS];
    for (i = 0; i <NUM_THREADS; i ++) {
        pt_ind = (int*) malloc(sizeof(i));
        *pt_ind = i;
        if (pthread_create(&(tid[i]),NULL,func,(void*)pt_ind) != 0){
            printf ( "pthread_create \n"); exit (1);
        }
    }
    sleep(3);
}