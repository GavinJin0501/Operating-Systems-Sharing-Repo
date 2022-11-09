#define _XOPEN_SOURCE 700

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

void compute() {
    int j;
    for (j = 0; j < 1E8; j ++);
}

void cleanup() {
    //TODO: Destroy your shared memory / semaphores
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
