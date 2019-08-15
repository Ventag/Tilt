CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
OUTPUTFILE = compiler
B4PATH = codegen
B3PATH = typecheck
B2PATH = expressions
B1PATH = symbols

OBJS = $(B1PATH)/*.o $(B2PATH)/*.o $(B3PATH)/*.o $(B4PATH)/*.o compiler.o

$(OUTPUTFILE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(B1PATH)/*.o:
	cd $(@D) && $(MAKE)

$(B2PATH)/*.o:
	cd $(@D) && $(MAKE)

$(B3PATH)/*.o:
	cd $(@D) && $(MAKE)

$(B4PATH)/*.o:
	cd $(@D) && $(MAKE)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	$(RM) $(OUTPUTFILE) $(OBJS) *~ && \
	cd $(B1PATH) && make clean && \
	cd ../$(B2PATH) && make clean && \
	cd ../$(B3PATH) && make clean && \
	cd ../$(B4PATH) && make clean \
