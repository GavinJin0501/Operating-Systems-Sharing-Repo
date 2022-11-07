#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>


int main() {
    sem_t* smutex;

    /* Creation of a semaphore mutex initialized to 1 */
    if ((smutex = sem_open("mysem", O_CREAT | O_EXCL | O_RDWR, 0666, 1)) == SEM_FAILED) {
        /* If the failure is caused by reason other than O_EXCL */
        if (errno != EEXIST) {
            perror("sem_open");
            exit(1);
        }

        /* Semaphore already created, open without O_CREAT */
        smutex = sem_open("mysem", O_RDWR);
    }

    /* P on smutex */
    sem_wait(smutex);

    /* V on smutex */
    sem_post(smutex);

    /* Close the semaphore */
    sem_close(smutex);

    /* Destroy the semaphore */
    sem_unlink("mysem");

    return EXIT_SUCCESS;
}