#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbols/memory.h"
#include "symbols/symbol.h"
#include "symbols/linkedlist.h"
#include "expressions/tree.h"
#include "expressions/pretty.h"
#include "typecheck/collect.h"
#include "typecheck/process.h"
#include "typecheck/verify.h"
#include "typecheck/weeder.h"
#include "codegen/ir_tree.h"
#include "codegen/ir_print.h"

int lineno;

int yyparse();

BODY *__main__;

int main(int argc, char** argv)
{
	lineno = 1;
	int i = yyparse();
	switch (i)
	{
	case -1: // parsing failure failure
		fprintf(stderr, "[compiler] parsing error: %s\n", yyerror());
		return -1;
		break;
	case 0: // succesful parse
		//print_begin(__main__);
		collect(__main__);
		process(__main__);
		verify(__main__);
		weeder(__main__);
		LINKEDLIST* irlist = build_ir_tree(__main__, 0);
		ir_print(irlist);
		break;
	}
	return 0;
}
