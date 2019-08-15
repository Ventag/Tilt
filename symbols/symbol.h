#ifndef __symbol_h
#define __symbol_h

#define HashSize 317

/*
 *SYMBOL will be extended later.
 * Function calls will take more parameters later.
 * */

typedef enum SYMBOL_TYPES
{
	SYMBOL_FUNC,
	SYMBOL_ID,
	SYMBOL_INT,
	SYMBOL_BOOL,
	SYMBOL_ARRAY,
	SYMBOL_RECORD,
	SYMBOL_NULL,
	SYMBOL_UNKNOWN
} SYMBOL_TYPES;

typedef enum SYMBOL_KINDS
{
	SYMBOL_LOCAL_VARIABLE,
	SYMBOL_PARAMETER,
	SYMBOL_RECORD_MEMBER,
	SYMBOL_TYPE_DEFINITION
} SYMBOL_KINDS;

typedef struct SYMBOL_VALUE
{
	struct SYMBOL_VALUE* array_next_value;
	struct SYMBOL_VALUE* return_type;
	struct SYMBOL_TABLE* child_scope;
	struct VAR_DECL_LIST* records;

	int length;
	SYMBOL_TYPES kind;
} SYMBOL_VALUE;

typedef struct SYMBOL
{
	char* name;
	int value;
	int parameters;
	int param_count;
	int offset;
	int var_offset;
	int table_id;
	struct SYMBOL *next;
	struct SYMBOL_VALUE *symbol_value;

	SYMBOL_TYPES symbol_type;
	SYMBOL_KINDS symbol_kind;
} SYMBOL;

typedef struct SYMBOL_TABLE
{
	SYMBOL *table[HashSize];
	struct SYMBOL_TABLE *next;
	struct SYMBOL_TABLE *parent;
	int table_id;
	int local_var_count;
} SYMBOL_TABLE;

int Hash(char *str);

SYMBOL_TABLE *initSymbolTable(int id);
SYMBOL_TABLE *scopeSymbolTable(SYMBOL_TABLE *t);
SYMBOL *putSymbol(SYMBOL_TABLE *t, char *name, SYMBOL_VALUE* value);
SYMBOL *getSymbol(SYMBOL_TABLE *t, char *name);
void dumpSymbolTable(SYMBOL_TABLE *t);

#endif