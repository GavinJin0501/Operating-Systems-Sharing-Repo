/**
 * Definition of a stack library
 **/

#define _XOPEN_SOURCE 700

// /* Stack structure */
// typedef struct astack{
// 	void* contents[STACK_SIZE];
// 	int top;
// } stack;

/* Initialization of the stack */
int init_stack();

/* Insert an element */
int push();

/* Extract an element */
void* pop();

/* Compute the size of the stack  */
int size();
