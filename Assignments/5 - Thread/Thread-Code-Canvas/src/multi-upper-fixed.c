#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define NB_THREAD 3

int nextFileIndex, totalFiles;
char** files;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void file_to_upper(char* fileName) {
    FILE *fp1, *fp2;
    char dest_fname[128];
    int c = 1;

    fp1 = fopen(fileName, "r");
    strcpy(dest_fname, fileName);
    strcat(dest_fname, ".UPPER.txt");
    // printf("%s\n", dest_fname);
    fp2 = fopen (dest_fname, "w");
    if ((fp1 == NULL) || (fp2 == NULL)) {
        perror ( "fopen");
        exit (1);
    }
    
    while (c != EOF) {
        c = fgetc(fp1);
        if (c != EOF)
            fputc(toupper(c), fp2);
//            fputc(toupper(c), stdout);
    }
    
    fclose (fp1);
    fclose (fp2);
    
}


void * thread_func(void* arg) {
    int localFileIndex;

    while (1) {
        pthread_mutex_lock(&m);
        if (nextFileIndex > totalFiles) { // all files are distributed
            pthread_mutex_unlock(&m);
            pthread_exit((void*) 0);
        } else {
            localFileIndex = nextFileIndex;
            nextFileIndex++;
        }
        pthread_mutex_unlock(&m);

        file_to_upper(files[localFileIndex]);
        printf("Thread %ld has conoverted file %s\n", (long) pthread_self(), files[localFileIndex]);
    }
    
    pthread_exit((void*) 0);
}


int main (int argc, char ** argv) {
    int i, j;
    pthread_t tid[NB_THREAD];

    nextFileIndex = 1;
    totalFiles = argc - 1;
    files = argv;
    
    for (i = 0; i < NB_THREAD; i++) {
        if (pthread_create(&(tid[i]), NULL, thread_func, NULL) != 0) {
            perror("pthread_create error\n");
            exit(1);
        }
    }

    for (j = 0; j < NB_THREAD; j++) {
        if (pthread_join(tid[j], NULL) != 0) {
            perror("pthread_join error\n");
            exit(1);
        } else {
            printf("Thread %d is done!\n", j);
        }
    }
    printf("Conversion is done!\n");
    return EXIT_SUCCESS;
}
