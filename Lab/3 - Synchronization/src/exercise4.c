#define _XOPEN_SOURCE 700
#define SHMNAME1 "myshm1"
#define SHMNAME2 "myshm2"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

//TODO: Declare your shared memory / semaphore structures and variables
typedef struct barrier_shared_memory {
    sem_t* mutex;
    sem_t* sem_block;
    int* finished;
    int n_pcs;
} barrier_shm;

barrier_shm* my_shm;

void compute() {
    int j;
    for (j = 0; j < 1E8; j ++);
}

void cleanup() {
    //TODO: Destroy your shared memory / semaphores
    sem_close(my_shm->mutex);
    sem_close(my_shm->sem_block);
    munmap(my_shm->finished, sizeof(int) * my_shm->n_pcs);
    shm_unlink(SHMNAME2);
    munmap(my_shm, sizeof(barrier_shm));
    shm_unlink(SHMNAME1);
}

/**
 * This function redefines the behavior of your executable
 * when you type Ctrl-C in the terminal: instead of terminating
 * directly, the main process will call cleanup()
 */
void init() {
    sigset_t mask;
    struct sigaction act;
    
    sigfillset(&mask);
    act.sa_handler = cleanup;
    act.sa_mask = mask;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
}

void wait_barrier(int pcs_nb) {
    //TODO: Write your synchronization
    int isSame = 1, i;
    
    sem_wait(my_shm->mutex);
    my_shm->finished[pcs_nb]++;
    for (i = 0; i < my_shm->n_pcs; i++) {
        if (i != pcs_nb && my_shm->finished[i] != my_shm->finished[pcs_nb]) {
            isSame = 0;
            break;
        }
    }
    sem_post(my_shm->mutex);
    
    if (isSame != 1) { // block n - 1
        sem_wait(my_shm->sem_block);
    } else {
        for (i = 0; i < my_shm->n_pcs - 1; i++) {
            sem_post(my_shm->sem_block);
        }
    }
}


int main(int argc , char **argv) {
    int i, j, pid;

    /* Check the main arguments */
    if (argc != 3) {
        printf("wrong usage: %s <# processes> <# loops>\n", argv[0]);
        exit (1);
    }
    int N_PCS = atoi(argv[1]);
    int N_LOOPS = atoi(argv[2]);

    //TODO: Setup your shared memory / semaphores
    int fd = shm_open(SHMNAME1, O_CREAT | O_RDWR, 0600);
    if (ftruncate(fd, sizeof(barrier_shm))) {
        perror("ftruncate");
        exit(-1);
    }
    my_shm = (barrier_shm*) mmap(0, sizeof(barrier_shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    my_shm->mutex = sem_open("/mutex", O_CREAT | O_RDWR, 0600, 1);
    my_shm->sem_block = sem_open("/sem_block", O_CREAT | O_RDWR, 0600, 0);
    my_shm->n_pcs = N_PCS;

    fd = shm_open(SHMNAME2, O_CREAT | O_RDWR, 0600);
    if (ftruncate(fd, sizeof(int) * N_PCS)) {
        perror("ftruncate");
        exit(-1);
    }
    my_shm->finished = (int*) mmap(0, sizeof(int) * N_PCS, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    for (i = 0; i < N_PCS; i++) {
        my_shm->finished[i] = 0;
    }

    /* Record the PID of the initial parent process */
    pid = getpid();

    init();

    for (i = 0; ((i < N_PCS - 1) && (fork() > 0)); i++);
    
    for (j = 0; j < N_LOOPS; j++) {
        compute();
        printf("%d(%d)> Before barrier #%d\n", getpid(), i, j);
        wait_barrier(i);
        printf("%d(%d)> After barrier #%d\n", getpid(), i, j);
        compute();
    }
    
    if (pid == getpid()) {
        for (i = 0; i < N_PCS -1; i++) {
            if (wait(NULL) == -1) {
                perror("wait");
                exit(2);
            }
        }
        cleanup();
    }
    
    return 0;
}
