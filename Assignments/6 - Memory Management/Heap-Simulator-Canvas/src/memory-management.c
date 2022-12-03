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
    // 1. Update the size
    freelist = result.found + allocation_size;
    heap[freelist] = heap[result.found] - allocation_size;
    heap[freelist + 1] = heap[result.found + 1];

    // 2. Update in the allocated mem
    ptr = (void*) (heap + result.found);
    heap[result.found] = size;
    heap[result.found + 1] = '\0';

    return ptr;
}


int heap_free(void *dz) {
    // TODO
    int index = ptr2ind(dz), size = heap[index], i;

    // 1. Empty the memory
    for (i = index; i < size; i++) {
        heap[i + 1] = '\0';
    }

    // 2. Assign the new 


    return 0;
}

int heap_defrag() {
    // TODO
    return 0;
}


