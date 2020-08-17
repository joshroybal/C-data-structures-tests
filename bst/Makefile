CC = gcc
CFLAGS = -ansi -pedantic-errors -O2
LFLAGS = -static -s

bst: main.o bst.o
	$(CC) $^ -o $@ $(LFLAGS)

main.o: main.c bst.h
	$(CC) $< -c $(CFLAGS)

bst.o: bst.c bst.h
	$(CC) $< -c $(CFLAGS)

.PHONY : clean
clean:
	$(RM) bst *.o *~
