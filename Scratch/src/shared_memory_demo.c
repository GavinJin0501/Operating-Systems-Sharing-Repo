#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// shared property
int* sp;

int main() {
    // file descriptor
    int fd, pid; 

    /* Create segment myshm */
    if ((fd = shm_open("myshm", O_CREAT | O_RDWR, 0600)) == -1) {
        perror("shm_open");
        exit(1);
    }

    /* Allocate enough memory to store a (shared) integer */
    if (ftruncate(fd, sizeof(int)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    /* Map the segment in shared RW mode */
    if ((sp = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);        
    }

    /* Access segment */
    if ((pid = fork()) == 0) {
        *sp = 0;
        printf("In the child, sp changes from %d ", *sp);
        *sp = 10;
        printf("to %d\n", *sp);
        exit(0);
    } else if (pid > 0) {
        wait(NULL);
        printf("In the parent, sp is %d\n", *sp);
    }

    /* Detach segment */
    munmap(sp, sizeof(int));

    /* Destroy * the segment */
    shm_unlink("myshm");

    return EXIT_SUCCESS;
}