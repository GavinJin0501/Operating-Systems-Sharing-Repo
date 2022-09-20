#include <list.h>
#include <stdlib.h>
#include <stdio.h>


void init_list(struct list_type *l) {
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}
	
	
void insert_head(struct list_type *l, void* element) {
	cell* new_cell = malloc(sizeof(cell));
	new_cell->content = element;
	new_cell->previous = NULL;
	new_cell->next = l->head;
	if (l->head != NULL)
		l->head->previous = new_cell;
	l->head = new_cell;
	if (l->tail == NULL)
			l->tail = l->head;
	l->size++;
}


void* extract_head(struct list_type *l) {
	/* TODO */
	void* to_return = NULL;

	if (l->head == NULL) {
		return to_return;
	}

	cell* old_head = l->head;
	cell* new_head = old_head->next;

	// remove the links
	old_head->next = NULL;
	if (new_head != NULL) {
		new_head->previous = NULL;
	}
	
	// change the head
	l->head = new_head;
	l->size--;

	// save the res
	to_return = old_head->content;
	old_head->content = NULL;

	// free memory
	free(old_head);
	old_head = NULL;	

	return to_return;
}


void* extract_tail(struct list_type *l) {
	/* TODO */
	void* to_return = NULL;

	if (l->tail == NULL) {
		return to_return;
	}


	cell* old_tail = l->tail;
	cell* new_tail = old_tail->previous;

	// remove the links
	old_tail->previous = NULL;
	if (new_tail != NULL) {
		new_tail->next = NULL;
	}

	// change the tail
	l->tail = new_tail;
	l->size--;

	// save the res
	to_return = old_tail->content;
	old_tail->content = NULL;

	// free memory
	free(old_tail);
	old_tail = NULL;

	return to_return;
}


int list_size(struct list_type *l) {
	/* TODO */
	// cell* curr = l->head;
	// int size = 0;

	// while (curr != NULL) {
	// 	size++;
	// 	curr = curr->next;
	// }

	// return size;
	return l->size;
}
	