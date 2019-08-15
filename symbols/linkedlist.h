#ifndef __linkedlist_h
#define __linkedlist_h

typedef struct LINKEDLIST
{
	void* data;
	struct LINKEDLIST* next;
} LINKEDLIST;

LINKEDLIST* link_initialize();
void link_push(LINKEDLIST*, void*);
int link_length(LINKEDLIST*);
char* link_seek(LINKEDLIST*, char*);

#endif /* END OF DLINKED_LIST_H */
