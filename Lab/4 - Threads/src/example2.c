#define _XOPEN_SOURCE 700
#define NUM_THREADS 2

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>

void * func_thread (void * arg) {
    printf ("Argument received:%s, thread_id:%ld\n", (char*)arg, (long) pthread_self ());
    pthread_exit ((void *) 0); 
}

int main (int argc, char ** argv) { 
    int i; 
    pthread_t tid[NUM_THREADS]; 
    for (i = 0; i < NUM_THREADS; i ++) {
        if (pthread_create(&(tid[i]), NULL, func_thread, "JJY") != 0) {
            printf ( "pthread_create \n");
            exit (1);
        }
    }
    sleep(2);
    return EXIT_SUCCESS;
}