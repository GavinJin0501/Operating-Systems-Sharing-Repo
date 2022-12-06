#include <os-memory.h>


void first_fit(int size, freezone* fz) {
    int found = freelist;
    int previous = -1;

    while ((found != -1) && (heap[found] < size)) {
        previous = found;
        found = heap[found + 1];
    }

    fz->previous = previous;
    fz->found = found;
}

void best_fit(int size, freezone* fz) {
    // TODO
    int temp_found = freelist, found = freelist;
    int temp_previous = -1, previous = -1;

    while (temp_found != -1) {
        if (heap[temp_found] >= size && heap[temp_found] < heap[found]) {
            found = temp_found;
            found = temp_previous;
        }
        temp_previous = temp_found;
        temp_found = heap[temp_found + 1];
    }

    fz->previous = previous;
    fz->found = found;
}

void worst_fit(int size, freezone* fz) {
    // TODO
    int temp_found = freelist, found = freelist;
    int temp_previous = -1, previous = -1;

    while (temp_found != -1) {
        if (heap[temp_found] >= size && heap[temp_found] > heap[found]) {
            found = temp_found;
            found = temp_previous;
        }
        temp_previous = temp_found;
        temp_found = heap[temp_found + 1];
    }

    fz->previous = previous;
    fz->found = found;
}


void* heap_malloc(int size) {
    freezone result;                    //free zone found for the allocation
    int allocation_size = size + 1;     //size of the allocated zone
    void *ptr = NULL;                   //pointer to the allocated zone
    
    find_free_zone(size, &result);
    
    //Cannot find a free zone
    if (result.found == -1)
        return NULL;
    
    // TODO
    int next_index;
    if (heap[result.found] - size >= MIN_BLOCK_SIZE) { // still valid sapce for the current freezone
        next_index = result.found + allocation_size;
        heap[next_index] = heap[result.found] - allocation_size;
        heap[next_index + 1] = heap[result.found + 1];
        heap[result.found] = size;
    } else {
        next_index = heap[result.found + 1];
    }

    if (result.previous != -1) {
        heap[result.previous + 1] = next_index;
    }
    if (result.found == freelist) {
        freelist = next_index;
    }

    ptr = (void*) (heap + result.found + 1);
    allocations[result.found / 2] = (heap + result.found);
    return ptr;
}


int heap_free(void *dz) {
    // TODO
    int index = ptr2ind(dz) - 1, next_i;

    // The pointer is not valid
    if (index < 0 || index > HEAP_SIZE) {
        return -1;
    } else if (allocations[index / 2] == NULL) {
        return -1;
    }

    // 1. Update freelist
    allocations[index / 2] = NULL;
    if (freelist == -1 || index < freelist) { // this freezone will be the new first freezone
        freelist = index;
    }

    // 2. Update the available freezones after
    next_i = index + heap[index] + 1;
    if (next_i < HEAP_SIZE && allocations[next_i / 2] == NULL) {
        heap[index] += heap[next_i] + 1;
        heap[index + 1] = heap[next_i + 1];
    } else {
        while (next_i < HEAP_SIZE && allocations[next_i / 2] != NULL) {
            next_i += *(allocations[next_i / 2]) + 1;
        }
        if (next_i < HEAP_SIZE - 1) {
            heap[index + 1] = next_i;
        }
    }

    // 3. Update the previous available freezone
    if (freelist != index) {
        next_i = freelist;
        while (next_i + heap[next_i] + 1 != index) { // find the previous freezone
            next_i = next_i + heap[next_i] + 1;
        }
        heap[next_i] += heap[index] + 1;
        heap[next_i + 1] = (heap[index + 1] == -1) ? -1 : index;
    }

    return 0;
}

int heap_defrag() {
    // TODO
    return 0;
}


