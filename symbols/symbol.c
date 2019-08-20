#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "symbol.h"


int get_string_length(char* str)
{
	if(str == NULL)
		return 0;

	size_t length = 0;
	while(*str != '\0')
	{
		length++;
		str++;
	}
	return length;
}

int Hash(char* str)
{
	if(str == NULL)
		return 0;

	size_t str_length = get_string_length(str);
	size_t hash = 0;
	for(size_t i = 0; i < str_length; i++)
	{
		char c = str[i];
		int tmp = c;
		hash = (hash * 2) + tmp;
	}

	return hash % HashSize;
}

SYMBOL_TABLE *initSymbolTable()
{
	SYMBOL_TABLE *t = NEW(SYMBOL_TABLE);
	for(size_t i = 0; i < HashSize; i++)
		t->table[i] = NULL;

	t->next = NULL;

	return t;
}

SYMBOL_TABLE *scopeSymbolTable(SYMBOL_TABLE *t)
{
	SYMBOL_TABLE* new_table = initSymbolTable();
	new_table->next = t;
	return new_table;
}

SYMBOL *putSymbol(SYMBOL_TABLE *t, char* name, TYPEINFO* value)
{
	int hash = Hash(name);

	SYMBOL* s = NEW(SYMBOL);
	s->name = name;
	s->typeinfo = value;

	if (t->table[hash] == NULL)
	{
		t->table[hash] = s;
		return s;
	}
	else
	{
		fprintf(stderr, "symbol already exists at position %i, chaining\n", hash);
		SYMBOL* tmp = t->table[hash];

		if (tmp->next == NULL)
		{
			tmp->next = s;
			return s;
		}
		else
		{
			while (tmp->next)
			{
				if(strcmp(tmp->name, name) == 0)
				{
					fprintf(stderr, "attempted to insert duplicate symbol\n");
					return tmp;
				}

				tmp = tmp->next;
				if (tmp->next == NULL)
				{
					tmp->next = s;
					return s;
				}
			}
		}
	}

	return s;
}

SYMBOL* getSymbol(SYMBOL_TABLE *t, char *name)
{
	if(t == NULL)
	{
		fprintf(stderr, "SymbolTable is NULL, tried retrieving %s\n", name);
		return NULL;
	}

	int hash = Hash(name);
	SYMBOL* symbol = t->table[hash];
	
	while (t)
	{
		symbol = t->table[hash];
		while (symbol)
		{
			if (strcmp(symbol->name, name) == 0)
				return symbol;
			else
				symbol = symbol->next;
		}
		t = t->next;
	}

	return symbol;
}

SYMBOL *getSymbolDepth(SYMBOL_TABLE *t, char *name, int *depth)
{
	if (t == NULL)
	{
		fprintf(stderr, "SymbolTable is NULL, tried retrieving %s\n", name);
		return NULL;
	}

	int hash = Hash(name);
	SYMBOL* symbol = t->table[hash];

	while (t)
	{
		symbol = t->table[hash];
		while (symbol)
		{
			if (strcmp(symbol->name, name) == 0)
				return symbol;
			else
				symbol = symbol->next;
		}
		depth++;
		t = t->next;
	}

	return symbol;
}

void dumpSymbolTable(SYMBOL_TABLE *t)
{
	size_t counter = 0;
	while(t)
	{
		fprintf(stderr, "table %ld\n", counter);
		for(size_t i = 0; i < HashSize; i++)
		{
			if(t->table[i])
			{
				SYMBOL* symbol = t->table[i];
				while(symbol)
				{
					fprintf(stderr, "|-> name = %s value = %d\n", symbol->name, symbol->typeinfo);
					symbol = symbol->next;
				}
			}
		}

		counter++;
		if(t->next == NULL)
			break;
		      
		t = t->next;

	}
	fprintf(stderr, "\nfinished dumping table\n");
}