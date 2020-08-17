CC = gcc
CFLAGS = -ansi -pedantic-errors -O2
LFLAGS = -static -s

avl: main.o avl.o
	$(CC) $^ -o $@ $(LFLAGS)

main.o: main.c avl.h
	$(CC) $< -c $(CFLAGS)

avl.o: avl.c avl.h
	$(CC) $< -c $(CFLAGS)

.PHONY : clean
clean:
	$(RM) avl *.o *~
