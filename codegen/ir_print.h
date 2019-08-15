#ifndef __ir_print_h
#define __ir_print_h

#include "../symbols/linkedlist.h"
#include "instruction_set.h"

void ir_print(LINKEDLIST*);
//void ir_print_args(ARGS*);

char* get_register_from_enum(REGISTER reg);

#endif // !__ir_tree_h
