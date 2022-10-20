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

void insert_back(task tasks[], sched_data* schedData, int i, int val) {
    while (i < MAX_NB_OF_TASKS - 1 && schedData->queues[0][i + 1] != -1) {
        schedData->queues[0][i] = schedData->queues[0][i + 1];
        i++;
    }
    schedData->queues[0][i] = val;
}

void init_queues(sched_data* schedData, int currentTime, int numOfQueues) {
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = numOfQueues;
        for (int i = 0; i < numOfQueues; i++) {
            for (int j = 0; j < MAX_NB_OF_TASKS; j++) {
                schedData->queues[i][j] = -1;
            }
        }
    }
}


int FCFS(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    
    int i, j;
    
    // Initialize single queue
    init_queues(schedData, currentTime, 1);
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
    init_queues(schedData, currentTime, 1);
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
    init_queues(schedData, currentTime, 1);
    admitNewTasks(tasks, nbOfTasks, schedData, currentTime);
    printQueues(tasks, schedData);

    // find if there is a running task
    j = 0;
    while (j < MAX_NB_OF_TASKS && (i = schedData->queues[0][j]) != -1 && tasks[i].state != RUNNING) j++;

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
            insert_back(tasks, schedData, j, i);
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
    init_queues(schedData, currentTime, 1);
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
            } else if (tasks[i].cyclesInQuantum == schedData->quantum) { // if the task finishes a quantum
                tasks[i].state = READY;
                tasks[i].cyclesInQuantum = 0;
                // put the current job to the end of the queue
                insert_back(tasks, schedData, j, i);
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
    init_queues(schedData, currentTime, QUEUES);
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
    int i, j, z, temp, task_i;

    // Initialize single queue
    init_queues(schedData, currentTime, 1);
    admitNewTasks(tasks, nbOfTasks, schedData, currentTime);
    printQueues(tasks, schedData);

    i = -1;         // index in tasks
    task_i = -1;    // index of the task in queue
    j = 0;
    while (j <= MAX_NB_OF_TASKS) {
        temp = schedData->queues[0][j];
        if (temp == -1) {
            break;
        } else if (tasks[temp].state == RUNNING) {
            i = temp;
            task_i = j;
        } else if (tasks[temp].state == SLEEPING) {
            if (currentTime - tasks[temp].ioEvictedDate == tasks[temp].ioTime) {
                if (tasks[temp].executionTime == tasks[temp].computationTime) {
                    tasks[temp].state = TERMINATED;
                    tasks[temp].completionDate = currentTime;
                    for (z = j; z < MAX_NB_OF_TASKS - 1; z++) {
                        schedData->queues[0][z] = schedData->queues[0][z+1];
                    }
                    j--;
                } else {
                    tasks[temp].state = READY;
                }
            } 
        }
        j++;
    }

    if (i != -1) {
        if (tasks[i].ioTime != 0) { // has io block
            if (tasks[i].executionTime == tasks[i].computationTime) {
                tasks[i].state = SLEEPING;
                tasks[i].ioEvictedDate = currentTime;
                insert_back(tasks, schedData, task_i, i);
            } else if (tasks[i].ioFrequency < schedData->quantum) {
                if (tasks[i].executionTime % tasks[i].ioFrequency == 0) {
                    tasks[i].state = SLEEPING;
                    tasks[i].ioEvictedDate = currentTime;
                    insert_back(tasks, schedData, task_i, i);
                } else if (tasks[i].cyclesInQuantum == schedData->quantum) {
                    tasks[i].state = READY;
                    tasks[i].cyclesInQuantum = 0;
                    insert_back(tasks, schedData, task_i, i);
                } else {
                    tasks[i].executionTime ++;
                    tasks[i].cyclesInQuantum ++;
                    return i;
                }
            } else if (tasks[i].ioFrequency > schedData->quantum) {
                if (tasks[i].cyclesInQuantum == schedData->quantum) {
                    tasks[i].state = READY;
                    tasks[i].cyclesInQuantum = 0;
                    insert_back(tasks, schedData, task_i, i);
                } else if (tasks[i].executionTime % tasks[i].ioFrequency == 0) {
                    tasks[i].state = SLEEPING;
                    tasks[i].ioEvictedDate = currentTime;
                    insert_back(tasks, schedData, task_i, i);
                } else {
                    tasks[i].executionTime ++;
                    tasks[i].cyclesInQuantum ++;
                    return i;
                }
            } else {
                if (tasks[i].cyclesInQuantum == schedData->quantum) {
                    tasks[i].state = SLEEPING;
                    tasks[i].cyclesInQuantum = 0;
                    tasks[i].ioEvictedDate = currentTime;
                    insert_back(tasks, schedData, task_i, i);
                } else {
                    tasks[i].executionTime ++;
                    tasks[i].cyclesInQuantum ++;
                    return i;
                }
            }
        } else { // does not have io block
            if (tasks[i].executionTime == tasks[i].computationTime) { // terminate it immediately
                tasks[i].state = TERMINATED;
                tasks[i].completionDate = currentTime;
                for (; task_i < MAX_NB_OF_TASKS - 1; task_i++) {
                    schedData->queues[0][task_i] = schedData->queues[0][task_i+1];
                }
            } else if (tasks[i].cyclesInQuantum == schedData->quantum) {
                tasks[i].state = READY;
                tasks[i].cyclesInQuantum = 0;
                insert_back(tasks, schedData, task_i, i);
            } else {
                tasks[i].executionTime ++;
                tasks[i].cyclesInQuantum ++;
                return i;
            }
        }
            
    } 

    // find the first ready task
    j = 0;
    while (j < MAX_NB_OF_TASKS && ((i = schedData->queues[0][j]) != -1) && tasks[i].state != READY) j++;
    if (i != -1) {
        tasks[i].state = RUNNING;
        tasks[i].executionTime ++;
        tasks[i].cyclesInQuantum ++;
        return i;
    }
    
    // No task could be elected
    return -1;
}
