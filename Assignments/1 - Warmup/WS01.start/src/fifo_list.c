#include <fifo.h>
#include <list.h>
#include <stdlib.h>

struct list_type QUEUE;

int init_queue() {
    init_list(&QUEUE);
    return list_size(&QUEUE);
}

int queue(void* element) {
    insert_head(&QUEUE, element);
    return list_size(&QUEUE);
};

void* dequeue() {
    return extract_tail(&QUEUE);
};

int size() {
    return list_size(&QUEUE);
}