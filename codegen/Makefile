CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
DEPS = instruction_set.h ir_tree.h ir_print.h
OBJS = instruction_set.o ir_tree.o ir_print.o

# main:
	# gcc *.c -o symbol
	
all: $(OBJS) $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	rm -f *.o
