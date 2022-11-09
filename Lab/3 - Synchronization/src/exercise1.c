#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

int* sp;
char* name = "myshm";

// Can the same fd be shared among different processes?
int main () {
    int i, pid, fd, sum = 0;
    
    if ((fd = shm_open(name, O_CREAT | O_RDWR, MAP_SHARED)) == -1) {
        perror("shm_open");
        exit(-1);
    }

    if (ftruncate(fd, sizeof(int) * N) == -1) {
        perror("ftruncate");
        exit(-1);
    }

    // parent map the segment
    if ((sp = mmap(NULL, sizeof(int) * N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(-1); 
    }

    for (i = 0; i < N && (pid = fork()) > 0; i++);      // create N processes

    if (i < N) { // child
        srand(getpid());
        *(sp + i) = rand() % 10;
        printf("In the child > my pid is: %d, random value is: %d\n", getpid(), *(sp + i));
    } else { // parent
        for (i = 0; i < N; i++) {
            wait(NULL);
        }

        printf("In the parent> the summation is ");
        for (i = 0; i < N; i++) {
            if (i == 0) {
                printf("%d ", *(sp + i));
            } else {
                printf("+ %d ", *(sp + i));
            }
            sum += *(sp + i);
        }
        printf("= %d\n", sum);
    }   

    munmap(sp, sizeof(int) * N);
    if (i == N) {
        shm_unlink(name);
    }

    return EXIT_SUCCESS;
}