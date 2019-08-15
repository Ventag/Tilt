# BachelorCompiler
## Group:
Frederik Wexø - frwex16

Philip Kristensen - phkri16

Simon Karing - sikar16

Ardit Gashi - argas16

### Part 1 - Symbol Table
To use these header files, include the header files first:

#include "symbol.h"
#include "memory.h"

You can use

NEW(SymbolTable);

to allocate space (of any type given as parameter).

to compile the program, install gcc and run the following command:
gcc *.c -o symbol

to execute the generated binary, run the following command (given symbol was the output name given)
./symbol

To run on mac change #include <malloc.h> to #include <malloc/malloc.h> 

### Part 2 - Scanner and Parser
exp.zip contains all files.

Run flex, bison, and compile by writing the following on the command line:

  make -f Makefile

To run, write the following on the command line:

  ./exp

Now you can type an expression ended by $ and <Ctrl>-D.
Example (leaving out the <Ctrl>-D):

  3*4-1/x$

## Project compiled using:
gcc -std=c11 -Wall -Wextra -pedantic
## Final report latex
https://www.overleaf.com/1689124754nngdhpcwynzs
## Reports in Google Drive
https://drive.google.com/drive/folders/1WTOQooyfBVuoH7RWte0QuZr29YtsrJp0?usp=sharing
