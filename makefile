.PHONY: run clean build
.IGNORE: clean
.DEFAULT_GOAL:=build

run: main.out
	./main.out

rerun: clean main.out
	./main.out

build: main.out
main.out: main.o rbtree.o
	gcc -Wall main.o rbtree.o -o main.out

clean:
	rm -fv main.o rbtree.o main.out

main.o : main.c rbtree.h
	gcc -Wall -c main.c -o main.o

rbtree.o : rbtree.c rbtree.h
	gcc -Wall -c rbtree.c -o rbtree.o
