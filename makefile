.PHONY: run clean build
.IGNORE: clean
.DEFAULT_GOAL:=build

run: main
	./main

rerun: clean main
	./main

build: main
main: main.o rbtree.o
	gcc -Wall main.o rbtree.o -o main

clean:
	rm -fv main.o rbtree.o main

main.o : main.c rbtree.h
	gcc -Wall -c main.c -o main.o

rbtree.o : rbtree.c rbtree.h
	gcc -Wall -c rbtree.c -o rbtree.o
