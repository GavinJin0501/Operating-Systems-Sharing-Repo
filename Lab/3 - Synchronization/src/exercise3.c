#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 6

sem_t* sprod[N];
sem_t* scons;
int* vals;


int main(int argc, char* argv[]) {
    int i, j, fd, total = 0;

    fd = shm_open("myshm", O_CREAT | O_RDWR, 0600);
    ftruncate(fd, sizeof(int) * N);
    vals = (int*) mmap(0, sizeof(int) * N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    char* s_name = (char*) malloc(sizeof(char) * 16);
    for (i = 0; i < N; i++) {
        sprintf(s_name, "sprod:%d", i);
        sprod[i] = sem_open(s_name, O_CREAT | O_RDWR, 0600, 0);
    }
    scons = sem_open("/scons", O_CREAT | O_RDWR, 0600, 0);

    for (i = 0; i < N && fork() > 0; i++);

    if (i < N) {
        srand(getpid());
        for (j = 0; j < N; j++) {
            vals[i] = rand() % 10;
            sem_post(scons);
            sem_wait(sprod[i]);
        }
        sem_close(sprod[i]);
		exit(0);
    } else {
        for (j = 0; j < N; j++) {
            for (i = 0; i < N; i++)
                // sem_wait(scons[i]);
                sem_wait(scons);
            for (i = 0; i < N; i++) {
                total += vals[i];
            }
            printf("Round %d:> sum is %d.\n", j, total);
            for (i = 0; i < N; i++)
                sem_post(sprod[i]);
        }
    }

    for (i = 0; i < N; i++) {
		wait(0);
        sem_close(sprod[i]);
        sprintf(s_name, "/sprod:%d", i);
        sem_unlink(s_name);
        sprintf(s_name, "/scons:%d", i);
        sem_unlink(s_name);
    }
    sem_close(scons);
    munmap(vals, N*sizeof(int));
    shm_unlink("myshm");
    
    printf("PP> Total sum of values received is %d\n", total);

	return 0;
}