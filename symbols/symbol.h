#ifndef __symbol_h
#define __symbol_h

#define HashSize 317

/*
 *SYMBOL will be extended later.
 * Function calls will take more parameters later.
 * */

typedef enum TYPES
{
	TYPE_FUNC,
	TYPE_ID,
	TYPE_INT,
	TYPE_BOOL,
	TYPE_ARRAY,
	TYPE_RECORD,
	TYPE_NULL,
	TYPE_UNKNOWN
} TYPES;

typedef enum SYMBOL_KIND
{
	LOCALVAR,
	PARAMETER,
	RECORD_MEMBER,
	TYPEDEF
} SYMBOL_KIND;

typedef struct TYPEINFO
{
	struct TYPEINFO* array_next_value;
	struct TYPEINFO* return_type;
	struct SYMBOL_TABLE* child_scope;
	struct VAR_DECL_LIST* records;

	int length;
	TYPES type;
} TYPEINFO;

typedef struct SYMBOL
{
	char* name;
	int param_count;
	int var_offset;
	int table_id;
	struct SYMBOL *next;
	struct TYPEINFO *typeinfo;

	TYPES type;
	SYMBOL_KIND kind;
} SYMBOL;

typedef struct SYMBOL_TABLE
{
	SYMBOL *table[HashSize];
	struct SYMBOL_TABLE *next;
	int local_var_count;
} SYMBOL_TABLE;

int Hash(char *str);

SYMBOL_TABLE *initSymbolTable();
SYMBOL_TABLE *scopeSymbolTable(SYMBOL_TABLE *t);
SYMBOL *putSymbol(SYMBOL_TABLE *t, char *name, TYPEINFO* value);
SYMBOL *getSymbol(SYMBOL_TABLE *t, char *name);
SYMBOL *getSymbolDepth(SYMBOL_TABLE *t, char *name, int *depth);
void dumpSymbolTable(SYMBOL_TABLE *t);

#endif