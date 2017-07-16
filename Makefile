CFLAGS = -Werror -Wshadow -Wall -O3 -g
GCC = gcc $(CFLAGS)

all: packing.o packing_main.o
	$(GCC) packing.c packing_main.c -o proj3

%.o: %.c packing.h
	$(GCC) -c $<

test: all
	./proj3 Given_Files/r6_po.txt output

mem: all
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes proj3 Given_Files/r0_po.txt output

clean:
	/bin/rm -f *.o
	/bin/rm -f proj3
	/bin/rm -f output
