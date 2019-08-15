#include <stdio.h>
#include "stack.h"
#include "memory.h"

STACK* init_stack()
{
	STACK* st = NEW(STACK);
	st->top = NULL;
	return st;
}

int is_stack_empty(STACK* st)
{
	if (st->top == NULL)
		return 1;

	return 0;
}

void push_stack(STACK* st, void* data)
{
	STACK_ELEMENT* link = NEW(STACK_ELEMENT);
	link->data = data;
	link->next = st->top;
	st->top = link;
}

void* peek_stack(STACK* st)
{
	if (is_stack_empty(st))
	{
		return NULL;
	}

	return st->top->data;
}

void* pop_stack(STACK* st)
{
	if (is_stack_empty(st))
	{
		return NULL;
	}

	void* ret;
	ret = st->top->data;
	st->top = st->top->next;
	return ret;
}