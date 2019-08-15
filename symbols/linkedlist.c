#include <stdio.h>
#include "linkedlist.h"
#include "memory.h"

LINKEDLIST* link_initialize()
{
	LINKEDLIST* head = (LINKEDLIST*)malloc(sizeof(LINKEDLIST));
	head->data = NULL;
	head->next = NULL;
	return head;
}
void link_push(LINKEDLIST* head, void* data)
{
	if (head->data == NULL)
	{
		head->data = data;
		head->next = NULL;
		return;
	}

	LINKEDLIST* iterator = head;
	while (iterator->next != NULL)
		iterator = iterator->next;

	LINKEDLIST* element = (LINKEDLIST*)malloc(sizeof(LINKEDLIST));
	element->data = data;
	element->next = NULL;
	iterator->next = element;
}
int link_length(LINKEDLIST* head)
{
	if (head->data == NULL)
		return -1;

	int count = 1;
	LINKEDLIST* iterator = head;
	while (iterator->next != NULL)
	{
		iterator = iterator->next;
		count++;
	}

	return count;
}

char* link_seek(LINKEDLIST* head, char* data)
{
	LINKEDLIST* iterator = head;
	while(iterator->next)
	{
		int val = strcmp(((char*)iterator->data), data);
		fprintf(stderr, "comparing %s and %s : %i\n", data, iterator->data, val);
		if(val == 0)
		{
			fprintf(stderr, "element found\n");
			return iterator->data;
		}
		iterator = iterator->next;
	}
	return NULL;
}