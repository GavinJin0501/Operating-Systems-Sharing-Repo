#include <list.h>
#include <stack.h>
#include <stdlib.h>

struct list_type stack;

int init_stack() {
    init_list(&stack);
    return list_size(&stack);
}

int push(void* element) {
    insert_head(&stack, element);
    return list_size(&stack);
}

void* pop() {
    return extract_head(&stack);
}

int size() {
    return list_size(&stack);
}