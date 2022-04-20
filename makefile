run:
	./main.out

rerun:
	make clean
	make build
	./main.out

build: main.o rbtree.o
	gcc -Wall main.o rbtree.o -o main.out

clean:
	rm -f main.o rbtree.o main.out

main.o :
	gcc -Wall -c main.c -o main.o

rbtree.o :
	gcc -Wall -c rbtree.c -o rbtree.o



