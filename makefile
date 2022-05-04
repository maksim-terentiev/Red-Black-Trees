.PHONY: run clean build
.IGNORE: clean
.DEFAULT_GOAL:=example

run: main
	./main

rerun: clean main
	./main

rune: example
	./example

clean:
	rm -fv main.o rbtree.o tree_print.o example.o main

build: main
main: main.o rbtree.o tree_print.o
	gcc -Wall main.o rbtree.o tree_print.o -o main

main.o : main.c rbtree.h tree_print.h
	gcc -Wall -c main.c -o main.o

rbtree.o : rbtree.c rbtree.h tree_print.h err_macro.h
	gcc -Wall -c rbtree.c -o rbtree.o

tree_print.o : tree_print.c tree_print.h
	gcc -Wall -c tree_print.c -o tree_print.o
	
example: example.o rbtree.o tree_print.o
	gcc -Wall example.o rbtree.o tree_print.o -o example

example.o: example.c rbtree.h tree_print.h
	gcc -Wall -c example.c -o example.o
