#include "weeder.h"
#include "../expressions/tree.h"
#include "../symbols/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STACK* stack;


BODY* weeder (BODY* body)
{
    fprintf(stderr, "[weeding] started\n");

    body = weed_body(body);

    return body;
}

BODY* weed_body(BODY* body)
{
    body->decl_list = weed_decl_list(body->decl_list);

    body->statement_list = weed_stmt_list(body->statement_list);

    return body;
}


FUNCTION* weed_func(FUNCTION* func)
{
    stack = init_stack();
    func->body->statement_list->statement->retval = 0;
    push_stack(stack, func);

    if(strcmp(func->head->id, func->tail->id) != 0)
    {
        fprintf(stderr, "Error at line %i: head and tail id of function does not match!\n", func->head->lineno);
        exit(1);
    }

    weed_head(func->head);
    weed_body(func->body);
    //if(func->body->statement_list->statement->retval == 0)
	if(((FUNCTION*)peek_stack(stack))->found_return_statement == 0)
    {
        fprintf(stderr, "Error at line %i: The function is missing a return statement\n", func->lineno);
        exit(1);
    }
    pop_stack(stack);

    return func;

}

VAR_DECL_LIST* weed_var_decl_list(VAR_DECL_LIST* var_decl_list)
{
    switch (var_decl_list->kind)
    {
        case VDECL_LIST:
            weed_var_decl_list(var_decl_list->var_decl_list);
            weed_var_type(var_decl_list->var_type);
            break;
        case VDECL_TYPE:
            weed_var_type(var_decl_list->var_type);
            break;
    }
    return var_decl_list;
}

PAR_DECL_LIST* weed_par_decl_list(PAR_DECL_LIST* par_decl_list)
{
    switch (par_decl_list->kind)
    {
        case PAR_DECL_LIST_POPLUATED:
            par_decl_list->var_decl_list = weed_var_decl_list(par_decl_list->var_decl_list);
            break;

        case PAR_DECL_LIST_EMPTY:
            break;
    }
    return par_decl_list;
}

TYPE* weed_type(TYPE* type)
{
    switch (type->kind)
    {
        case ARRAY_T:
            type->val.type = weed_type(type->val.type);
            break;
        
        case RECORD_T:
            type->val.var_decl_list = weed_var_decl_list(type->val.var_decl_list);
            break;
        
        default:
            break;
    }
    return type;
}

HEAD* weed_head(HEAD* head)
{
    head->par_decl_list = weed_par_decl_list(head->par_decl_list);
    head->type = weed_type(head->type);

    return head;
}

VAR_TYPE* weed_var_type(VAR_TYPE* var_type)
{
    weed_type(var_type->type);

    return var_type;
}

DECL_LIST* weed_decl_list(DECL_LIST* decl_list)
{
    switch (decl_list->kind)
    {
    case PAR_DECL_LIST_POPLUATED:
        weed_declaration(decl_list->declaration);
        weed_decl_list(decl_list->decl_list);
        break;
    
    case DECL_LIST_EMPTY:
        break;

    }

    return decl_list;
}

DECLARATION* weed_declaration(DECLARATION* declaration)
{
    switch(declaration->kind)
    {
        case DECLARATION_VAR:
            declaration->val.var_decl_list = weed_var_decl_list(declaration->val.var_decl_list);
            break;

        case DECLARATION_ID:
            declaration->val.identifier.type = weed_type(declaration->val.identifier.type);
            break;

        case DECLARATION_FUNC:
            declaration->val.function = weed_func(declaration->val.function);
            break;

        default:
            break;
    }

    return declaration;
}
int counter = 0;
STATEMENT_LIST* weed_stmt_list(STATEMENT_LIST* stmt_list)
{
    switch (stmt_list->kind)
    {
        case STATEMENT_LIST_LIST:
			stmt_list->statement_list = weed_stmt_list(stmt_list->statement_list);
			stmt_list->statement = weed_stmt(stmt_list->statement);

            /*if(stmt_list->statement_list->statement->retval == 1)
            {
				fprintf(stderr, "skipping dead code\n");
                return stmt_list->statement_list;
            }*/

			counter++;
            break;

        case STATEMENT_LIST_ELEMENT:
            stmt_list->statement = weed_stmt(stmt_list->statement);
            break;
    }
    return stmt_list;
}

STATEMENT* weed_stmt(STATEMENT* stmt)
{
    int ifcaseReturn;
    int elsecaseReturn;
    TERM* term;

    switch(stmt->kind)
    {
        case RETURN:
        if (is_stack_empty(stack) )
        {
			fprintf(stderr, "Error @ %d - can't return outside a function\n");
            exit(1);
        }
        stmt->retval = 1;
		((FUNCTION*)peek_stack(stack))->found_return_statement = 1;
        return stmt;

        case IF:
            stmt->val.stat_if.stat = weed_stmt(stmt->val.stat_if.stat);
            
            stmt->val.stat_if.optional_else = weed_stmt_else(stmt->val.stat_if.optional_else);

            if(stmt->val.stat_if.optional_else->kind == ELSE_INACTIVE)
            {
                if(stmt->val.stat_if.condition->kind == EXP_TERM)
                {
                    term = stmt->val.stat_if.condition->val.term;

                    //when if statement is true and there is no else statement,
                    // then just replace the if statement with just its statement
                    if(term->kind == TERM_TRUE)
                    {
                        return stmt->val.stat_if.stat;
                    }
                }
            } else {
                ifcaseReturn = stmt->val.stat_if.stat->retval;
                elsecaseReturn = stmt->val.stat_if.optional_else->statement->retval;

                //we have a case where there exists a return,
                // in both the if- and else-statement.
                //we will thus ignore everything after the if and else statement
                if(ifcaseReturn && elsecaseReturn)
                {
                    stmt->retval = 1;
                }

                if(stmt->val.stat_if.condition->kind == EXP_TERM)
                {
                    term = stmt->val.stat_if.condition->val.term;
                    if(term->kind == TERM_FALSE)
                    {   //when the if-statement is false, we only needs to look
                        // at the else-statement
                        return stmt->val.stat_if.optional_else->statement;
                    }else if(term->kind == TERM_TRUE)
                    {   //when the if-statement is true,
                        //then we only need to look at the if-statement
                        return stmt->val.stat_if.stat;
                    }
                }
            }

            break;
		default:
			break;
    }
    return stmt;
}

STATEMENT_ELSE* weed_stmt_else(STATEMENT_ELSE* stmt_else)
{
    switch(stmt_else->kind)
    {
        case ELSE_ACTIVE:
            stmt_else->statement = weed_stmt(stmt_else->statement);
            break;

        case ELSE_INACTIVE:
            break;
    }
    return stmt_else;
}




