#ifndef __stack_h
#define __stack_h
#include "../expressions/tree.h"

typedef struct STACK_ELEMENT
{
	void* data;
	struct STACK_ELEMENT* next;
} STACK_ELEMENT;

typedef struct STACK
{
	STACK_ELEMENT* top;
} STACK;

int is_stack_empty(STACK* st);
STACK* init_stack();

void* peek_stack(STACK* st);
void push_stack(STACK* st, void* data);
void* pop_stack(STACK* st);
#endif