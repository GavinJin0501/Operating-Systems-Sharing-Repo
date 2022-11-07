#define _XOPEN_SOURCE 700

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>

#define N 10

int* sp;
char* name = "myshm";
sem_t *sem1, *sem2;

int getSum() {
    int sum = 0;

    for (int i = 0; i < N; i++) {
        sum += *(sp + i);
    }

    return sum;
}

int main () {
    int i, pid, fd;
    
    // Can fd be shared among different processes?
    if ((fd = shm_open(name, O_CREAT | O_RDWR, MAP_SHARED)) == -1) {
        perror("shm_open");
        exit(-1);
    }

    if (ftruncate(fd, sizeof(int) * N) == -1) {
        perror("ftruncate");
        exit(-1);
    }

    if ((sem1 = (sem_t*) sem_open("sem1", O_CREAT | O_RDWR, 0666, 0)) == SEM_FAILED) {
        perror("sem_open: sem1");
        exit(-1);
    }

    if ((sem2 = (sem_t*) sem_open("sem2", O_CREAT | O_RDWR, 0666, 0)) == SEM_FAILED) {
        perror("sem_open: sem2");
        exit(-1);
    }
    
    // parent map the segment
    if ((sp = (int*) mmap(NULL, sizeof(int) * N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(-1); 
    }

    // create N processes
    for (i = 0; i < N && (pid = fork()) > 0; i++);

    if (i < N) { // child
        srand(getpid());
        *(sp + i) = rand() % 10;
        printf("In the child%d> my pid is: %d, random value is: %d\n", i, getpid(), *(sp + i));
        sem_post(sem1);
        sem_wait(sem2);
        printf("In the child%d> the sum is: %d\n", i, getSum());
    } else { // parent

        for (i = 0; i < N; i++) {
            sem_wait(sem1);
        }

        for (i = 0; i < N; i++) {
            sem_post(sem2);
        }

        sem_close(sem1);
        sem_close(sem2);
        sem_unlink("sem1");
        sem_unlink("sem2");

        munmap(sp, sizeof(int) * N);
        shm_unlink(name);
    }   

    return EXIT_SUCCESS;
}