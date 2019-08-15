#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "symbol.h"

char *randstring(int length) 
{
	static int mySeed = 25031984;
	char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	size_t stringLen = strlen(string);
	char *randomString = NULL;

	srand(time(NULL) * length + ++mySeed);

	if (length < 1) {
		length = 1;
	}

	randomString = malloc(sizeof(char) * (length + 1));

	if (randomString) {
		short key = 0;

		for (int n = 0; n < length; n++) {
			key = rand() % stringLen;
			randomString[n] = string[key];
		}

		randomString[length] = '\0';

		return randomString;
	}
	else {
		printf("No memory");
		exit(1);
	}
}

/*int main()
{
	SYMBOL_TABLE* table1 = initSymbolTable(0);
	SYMBOL_TABLE* table2 = scopeSymbolTable(table1);
	SYMBOL_TABLE* table3 = scopeSymbolTable(table2);
	SYMBOL_TABLE* table4 = scopeSymbolTable(table3);
	SYMBOL_TABLE* table5 = scopeSymbolTable(table4);

	SYMBOL* symbol = putSymbol(table1, "tilt", 1);
	SYMBOL* hit1 = putSymbol(table1, "sLqq", 1);
	SYMBOL* hit2 = putSymbol(table1, "TLo0", 1);
	SYMBOL* hit3 = putSymbol(table3, "TLo0", 3);
	SYMBOL* hit4 = putSymbol(table2, "xn6j", 2);
	SYMBOL* hit5 = putSymbol(table2, "yJxn", 2);
	SYMBOL* hit6 = putSymbol(table2, "tclJ", 2);
	printf("\n\n");
	SYMBOL* get = getSymbol(table1, "tilt");
	SYMBOL* getc = getSymbol(table5, "tclJ");
	SYMBOL* sporadic = getSymbol(table5, "TLo0");

	if (sporadic)
		printf("found symbol %s %i\n", sporadic->name, sporadic->value);
	else
		printf("SOMETHING WENT WRONG\n");

	if (getc)
		printf("found symbol %s %i\n", getc->name, getc->value);
	else
		printf("SOMETHING WENT WRONG\n");


	dumpSymbolTable(table5);
}*/
