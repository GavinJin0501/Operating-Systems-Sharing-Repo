
First Name: Jiayao

Last Name: Jin

NYU ID: jj2915

=======================================================================================
Files submitted:

src:
	fifo_list.c: Question 4
	fifo_test.c: Question 4
	list_impl.c: Question 2, Question 3, Question 4
	stack_array.c: Question 1
	stack_list.c: Question 3
	stack_test.c: Question2, Question 3

include:
	fifo.h: Question 4
	list.h: Question 3, Question 4
	stack.h: Question 1, Question 2, Question 3


=======================================================================================
Compilation rules in the Makefile:

# A few examples below
# make doublell: 	compile the doubly linked list implementation (Q2)
# make newlibstack:	recompiles the stack, implemented as a double-linked list, then integrates it in an update of libstack.a (Q3)
# make libfifo: 	compiles a dynamic queue implemented as a double-linked list, then integrates it in a library (lib/libfifo.a) (Q4)

Mine:
make doublell: compile the doubly linked list implementation (Q2)
make newlibstack: recompiles the stack, implemented as a double-linked list, then integrates it in an update of libstack.a (Q3)
make testlibstack: compiles the test for stack using our library for stack (Q3)
make runtestlibstack: calling newlibstack and testlibstack to run the test (Q3)
make libfifo: compiles a dynamic queue implemented as a double-linked list, then integrates it in a library (lib/libfifo.a) (Q4)
make testlibfifo: compiles the test for queue using our library for queue (Q4)
make runtestlibfifo: calling libfifo and testlibfifo to run the test (Q4)

=======================================================================================
Comments:



=======================================================================================
Textual answers: 

Question 5: Changes could be made in list.h and list_impl.c. Steps:
	1. We can add another attribute `int size` inside `struct list_type`.
	2. Inside the `init_list(struct list_type *l)`, we set `l->size = 0`.
	3. Inside the `insert_head(struct list_type *l`, we set `l->size++`.
	4. Inside the `extract_head(struct list_type *l)` and `extract_tail(struct list_type *l)`, if is successfully extracted, we set `l->size--`.
	5. For `list_size(struct list_type *l)`, we simply return `l->size`.


	