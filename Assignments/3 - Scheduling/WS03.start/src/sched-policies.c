#include <os-scheduling.h>

#define MODE_SJF 1
#define MODE_SRTF 2

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

// return the index in tasks[] of the shortest job (total time/remaining time)
// mode: 1 - SJF, 2 - SRTF
int getShortestJobIndex(task tasks[], sched_data* schedData, int mode) {
    int i = 0;                                      // index to traverse schedData->queues
    int ans = schedData->queues[0][i];              // store the answer
    int shortest_time = (mode == 1) ? tasks[ans].computationTime : tasks[ans].computationTime - tasks[ans].executionTime;
    int temp_ans;                                   // intermediate ans
    
    while ((temp_ans = schedData->queues[0][i]) != -1) {
        int temp_time = (mode == 1) ? tasks[temp_ans].computationTime : tasks[temp_ans].computationTime - tasks[temp_ans].executionTime;
        if (temp_time  < shortest_time) {
            ans = temp_ans;
            shortest_time = temp_time;
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
    while (j < MAX_NB_OF_TASKS && (i = schedData->queues[0][j]) != -1 && tasks[i].state != RUNNING) j++;

    /* i is the index of the task that is running if j is valid */ 
    if (i != -1 && tasks[i].state == RUNNING) {
        // if finished, terminate it, remove it from the queue, and elect a new task
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
    }

    // Otherwise, try to elect a new task if no task 
    if ((i = getShortestJobIndex(tasks, schedData, MODE_SJF)) != -1){
        tasks[i].executionTime ++;
        tasks[i].state = RUNNING;
        return i;
    }
    
    // No task could be elected
    return -1;
}


int SRTF(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (LAB Q3)
    int i, j, sr_job;

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

    // find if there is a running task
    j = 0;
    while (j <= MAX_NB_OF_TASKS && (i = schedData->queues[0][j]) != -1 && tasks[i].state != RUNNING) j++;

    // if there is a running task with index i
    if (i != -1 && tasks[i].state == RUNNING) { 
        if (tasks[i].executionTime == tasks[i].computationTime) { // if running task has finished
            tasks[i].state = TERMINATED;
            tasks[i].completionDate = currentTime;
            for (; j < MAX_NB_OF_TASKS - 1; j++) {
                schedData->queues[0][j] = schedData->queues[0][j+1];
            }
        } else if (i != getShortestJobIndex(tasks, schedData, MODE_SRTF)) { // if running task does not have the shortest remaining time
            tasks[i].state = READY;
        } else {
            tasks[i].executionTime ++;
            return i;
        }
    } 

    // Otherwise, try to elect a new task 
    if ((sr_job = getShortestJobIndex(tasks, schedData, MODE_SRTF)) != -1) {
        tasks[sr_job].executionTime ++;
        tasks[sr_job].state = RUNNING;
        return sr_job;
    }

    // No task could be elected
    return -1;
}


int RR(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (ASSIGNMENT Q1)
    int i, j = 0;

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
    
    if ((i = schedData->queues[0][0]) != -1) {
        // if the first task in the queue is running
        if (tasks[i].state == RUNNING) {
            if (tasks[i].executionTime == tasks[i].computationTime) {  // if the task has finished
                tasks[i].state = TERMINATED;
                tasks[i].completionDate = currentTime;
                for (; j < MAX_NB_OF_TASKS - 1; j++) {
                    schedData->queues[0][j] = schedData->queues[0][j+1];
                }
            } else if (tasks[i].cyclesInQuantum % schedData->quantum == 0) { // if the task finishes a quantum
                tasks[i].state = READY;
                tasks[i].cyclesInQuantum = 0;
                // put the current job to the end of the queue
                while (j < MAX_NB_OF_TASKS - 1 && schedData->queues[0][j+1] != -1) {
                    schedData->queues[0][j] = schedData->queues[0][j+1];
                    j++;
                }
                schedData->queues[0][j] = i;
            } else {
                tasks[i].executionTime ++;
                tasks[i].cyclesInQuantum ++;
                return i;
            }
        }
    }

    // otherwise, elect the first task
    if ((i = schedData->queues[0][0]) != -1) {
        tasks[i].state = RUNNING;
        tasks[i].executionTime ++;
        tasks[i].cyclesInQuantum ++;
        return i;
    }
    
    // No task could be elected
    return -1;
}

int MFQ(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (ASSIGNMENT Q2)
    int i, j, z, QUEUES = 3;

    // Initialize multi-level queue (3 levels)
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = QUEUES;
        for (i = 0; i < QUEUES; i++) {
            for (j = 0; j < MAX_NB_OF_TASKS; j++) {
                schedData->queues[i][j] = -1;
            }
        }
    }

    admitNewTasks(tasks, nbOfTasks, schedData, currentTime);
    printQueues(tasks, schedData);

    // get the task i that is running: must be one of the heads of each queue
    j = 0;
    while (j < QUEUES && !((i = schedData->queues[j][0]) != -1 && tasks[i].state == RUNNING)) j++;

    if (i != -1 && tasks[i].state == RUNNING) {
        if (tasks[i].executionTime == tasks[i].computationTime) {
            tasks[i].state = TERMINATED;
            tasks[i].completionDate = currentTime;
            for (z = 0; z < MAX_NB_OF_TASKS - 1; z++) {
                schedData->queues[j][z] = schedData->queues[j][z+1];
            }
        } else if (tasks[i].cyclesInQuantum % ((j + 1) * schedData->quantum) == 0) { 
            tasks[i].state = READY;
            tasks[i].cyclesInQuantum = 0;
            for (z = 0; z < MAX_NB_OF_TASKS - 1; z++) {
                schedData->queues[j][z] = schedData->queues[j][z+1];
            }
            
            z = 0;  // next available index to insert the current tasks[i] in the "next" level
            while (schedData->queues[(j + 1) % QUEUES][z] != -1) z++;
            schedData->queues[(j + 1) % QUEUES][z] = i;
        } else {
            tasks[i].executionTime ++;
            tasks[i].cyclesInQuantum ++;
            return i;
        }
    }

    j = 0; // potential index of queue (0, 1, 2)
    while (j < QUEUES && (i = schedData->queues[j][0]) == -1) j++;
    if (i != -1) {
        tasks[i].state = RUNNING;
        tasks[i].executionTime ++;
        tasks[i].cyclesInQuantum ++;
        return i;
    }
    
    // No task could be elected
    return -1;
}

int IORR(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //TODO (ASSIGNMENT BONUS)
    int i, j;


    
    // No task could be elected
    return -1;
}
