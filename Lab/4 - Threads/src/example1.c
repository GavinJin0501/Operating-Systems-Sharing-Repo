#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>

void *test (void *arg) {
    int i;
    printf("tid:%ld> Received=%s\n", (long)pthread_self(), (char*)arg); 
    for (i = 0; i <1E6; i ++);
    printf("end of secondary thread %ld\n", (long)pthread_self()); 
    return NULL;
}

int main (int argc, char ** argv) {
    pthread_t tid;
    if (pthread_create(&tid, NULL, test, "HELLO") != 0) {
        perror("pthread_create\n"); 
        exit (1); 
    } 
    
    sleep (3);
    printf ( "end of main thread\n");
    
    return EXIT_SUCCESS; 
}