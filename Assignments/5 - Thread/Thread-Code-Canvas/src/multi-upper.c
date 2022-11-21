#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>


void* file_to_upper(void* arg) {
    FILE *fp1, *fp2;
    char dest_fname[128];
    int c = 1;

    fp1 = fopen((char*) arg, "r");
    strcpy(dest_fname, (char*) arg);
    strcat(dest_fname, ".UPPER.txt");
    printf("%s\n", dest_fname);
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
    
    pthread_exit(NULL);
}


int main (int argc, char ** argv) {
    int i, j;
    pthread_t tid[argc - 1];
    
    for (i = 0; i < argc - 1; i++) {
        if (pthread_create(&(tid[i]), NULL, file_to_upper, (void*) argv[i + 1])) {
            perror("pthread_create error\n");
            exit(1);
        }
    }

    for (j = 0; j < argc - 1; j++) {
        if (pthread_join(tid[j], NULL) != 0) {
            perror("pthread_join error\n");
            exit(1);
        } else {
            printf("Thread %d for file %s is done!\n", j, argv[j + 1]);
        }
    }
    printf("Conversion is done!\n");
    return EXIT_SUCCESS;
}
