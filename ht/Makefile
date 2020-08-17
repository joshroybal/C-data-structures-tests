CC = gcc
CFLAGS = -ansi -pedantic-errors -O2
LFLAGS = -static -s

ht: main.o hash.o
	$(CC) $^ -o $@ $(LFLAGS)

main.o: main.c hash.h
	$(CC) $< -c $(CFLAGS)

hash.o: hash.c hash.h
	$(CC) $< -c $(CFLAGS)

.PHONY : clean
clean:
	$(RM) ht *.o *~
