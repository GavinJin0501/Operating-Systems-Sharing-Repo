#include <philosophers.h>


#define _XOPEN_SOURCE 700
#define PHISHM_NAME "/phishm:0"


typedef struct philosophers_shared_memory{
    // Declare shared memory and semaphores for synchronization among philosophers
    /**** TODO ****/
} philo_shm;

philo_shm *my_shm;


void initialize_shared_memory() {
    // Allocate and initialize shared memory segment and semaphores
    /**** TODO ****/
}

void pick_up_chopsticks(int rank) {
    // Protocol to pick up chopsticks
    // MUST call both of the following functions:
    //      void pick_up_left_chopstick(int rank);
    //      void pick_up_right_chopstick(int rank);
    /**** TODO ****/
}


void put_down_chopsticks(int rank) {
    // Protocol to pick up chopsticks
    // MUST call both of the following functions:
    //      void put_down_left_chopstick(int rank);
    //      void put_down_right_chopstick(int rank);
    /**** TODO ****/
}


void cleanup() {
    // Clean up shared memory segment and semaphores
    /**** TODO ****/
}


void philosopher(int rank) {
    int i;
    
    printf("%d> Philo %d is at the table\n", getpid(), rank);
    srand(getpid());

    for (i = 0; i < MEALS; i++) {
        printf("%d> Philo %d is thinking\n", getpid(), rank);
        sleep(rand()%2+1);
        printf("%d> Philo %d is hungry\n", getpid(), rank);
        pick_up_chopsticks(rank);
        eat_meal(rank);
        sleep(rand()%2+1);
        put_down_chopsticks(rank);
    }

    printf("%d> Philo %d is leaving the table\n", getpid(), rank);
    exit(0);
}
