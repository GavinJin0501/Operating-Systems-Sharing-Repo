#include <os-scheduling.h>


int admitNewTasks(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    int i, j;
    j = 0;
    while (schedData->queues[0][j] != -1)
        j++;
    for(i = 0; i < nbOfTasks; i++) {
        if ((tasks[i].state == UPCOMING) && (tasks[i].arrivalDate == currentTime)) {
            tasks[i].state = READY;
            schedData->queues[0][j] = i;
            j++;
        }
    }
    return 1;
}

// return the index in tasks[] of the shortest job
int getShortestJobIndex(task tasks[], sched_data* schedData, int* iOfQueue) {
    if (schedData->queues[0][0] == -1) {
        return -1;
    }

    int i = 0;                                      // index to traverse schedData->queues
    int ans = schedData->queues[0][i];              // store the answer
    int shortest_time = tasks[ans].computationTime;
    int temp_ans;                                   // intermediate ans
    *iOfQueue = i;
    
    while ((temp_ans = schedData->queues[0][i]) != -1) {
        if (tasks[temp_ans].computationTime < shortest_time) {
            ans = temp_ans;
            shortest_time = tasks[temp_ans].computationTime;
            *iOfQueue = i;
        }
        i++;
    }
    
    return ans;
}


int FCFS(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    
    int i, j;
    
    // Initialize single queue
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i = 0; i < MAX_NB_OF_TASKS; i++) {
            schedData->queues[0][i] = -1;
        }
    }
    
    admitNewTasks(tasks, nbOfTasks, schedData, currentTime);
    printQueues(tasks, schedData);
    
    // Is the first task in the queue running? Has that task finished its computations?
    //   If so, put it in terminated state and remove it from the queue
    //   If not, continue this task
    i = schedData->queues[0][0];
    if (i != -1) {
        if (tasks[i].state == RUNNING) {
            if (tasks[i].executionTime == tasks[i].computationTime) {
                tasks[i].state = TERMINATED;
                tasks[i].completionDate = currentTime;
                for (j = 0; j < MAX_NB_OF_TASKS - 1; j++) {
                    schedData->queues[0][j] = schedData->queues[0][j+1];
                }
            } else {
                /* Reelect this task */
                tasks[i].executionTime ++;
                return i;
            }
        }
    }
    
    // Otherwise, elect the first task in the queue
    i = schedData->queues[0][0];
    if (i != -1){
        tasks[i].executionTime ++;
        tasks[i].state = RUNNING;
        return i;
    }
    
    // No task could be elected
    return -1;
}


int SJF(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (LAB Q3)
    int i, j;

    // Initialize single queue
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i = 0; i < MAX_NB_OF_TASKS; i++) {
            schedData->queues[0][i] = -1;
        }
    }

    admitNewTasks(tasks, nbOfTasks, schedData, currentTime);
    printQueues(tasks, schedData);

    // Find if there is a still running job (which is the shortest job from last state)
    //      i is the index in the task
    //      j is the index in the job queue
    j = 0;
    while ((i = schedData->queues[0][j]) != -1) {
        /* if it is running, check if it has finished */ 
        if (tasks[i].state == RUNNING) {
            /* f finished, terminate it and remove it from the queue */
            if (tasks[i].executionTime == tasks[i].computationTime) {
                tasks[i].state = TERMINATED;
                tasks[i].completionDate = currentTime;
                for (; j < MAX_NB_OF_TASKS - 1; j++) {
                    schedData->queues[0][j] = schedData->queues[0][j+1];
                }
            } else {
                /* if not, reelect this task */
                tasks[i].executionTime ++;
                return i;
            }
            break;
        } else {
            j++;
        }
    }

    // Otherwise, elect the shortest job
    i = getShortestJobIndex(tasks, schedData, &j);
    if (i != -1){
        tasks[i].executionTime ++;
        tasks[i].state = RUNNING;
        return i;
    }

    // No task could be elected
    return -1;
}


int SRTF(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (LAB Q3)
    return -1;
}


int RR(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (ASSIGNMENT Q1)
    return -1;
}

int MFQ(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (ASSIGNMENT Q2)
    return -1;
}

int IORR(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (ASSIGNMENT BONUS)
    return -1;
}
