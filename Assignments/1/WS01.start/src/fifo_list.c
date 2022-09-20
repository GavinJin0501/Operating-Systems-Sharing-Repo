#include <fifo.h>
#include <list.h>
#include <stdlib.h>

struct list_type QUEUE;

int init_queue() {
    init_list(&QUEUE);
    return 0;
}

int queue(void* element) {
    insert_head(&QUEUE, element);
    return 0;
};

void* dequeue() {
    return extract_tail(&QUEUE);
};

int size() {
    return list_size(&QUEUE);
}