# CC = gcc
# CFLAGS = -std=c11 -Wall -Wextra -pedantic
#
# all: collect.h
# 	$(CC) $(CFLAGS) -c $? -o $@

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g
DEPS = ./*.h
OBJS = collect.o process.o verify.o weeder.o

all: $(OBJS) $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o
