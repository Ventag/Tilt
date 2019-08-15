CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g 
DEPS = stack.h symbol.h memory.h linkedlist.h
OBJS = stack.o symbol.o memory.o linkedlist.o

# main:
	# gcc *.c -o symbol
	
all: $(OBJS) $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	rm -f *.o
