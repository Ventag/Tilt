CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g

src = $(wildcard *.c)
obj = $(src:.c=.o)
hdr = $(src:.c=.h)

all:	y.tab.o lex.yy.o main.o tree.h tree.o pretty.h pretty.o
	$(CC) lex.yy.o y.tab.o tree.o pretty.o main.o -o exp -lfl

# all: $(obj) lex.yy.c y.tab.c tree.h pretty.h memory.h
#
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $? -o $@

y.tab.c y.tab.h:	exp.y
	bison -y -d exp.y

lex.yy.c:	exp.l y.tab.h
	flex exp.l

clean:
	rm -f *.o lex.yy.c y.tab.h y.tab.c
