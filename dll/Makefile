CC = clang
CFLAGS = -ansi -pedantic-errors -O2
LFLAGS = -static -s

dll: main.o list.o
	$(CC) $^ -o $@ $(LFLAGS)

main.o: main.c list.h
	$(CC) $< -c $(CFLAGS)

list.o: list.c list.h
	$(CC) $< -c $(CFLAGS)

.PHONY : clean
clean:
	$(RM) dll *.o *~
