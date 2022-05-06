.PHONY: run rerun clean build help
.IGNORE: clean

CC=gcc
CFLAGS=-Wall
RM=rm -fv

# .DEFAULT_GOAL:=example

all: main example

help:
	@echo "all   - cкомпилировать все программы"
	@echo "help  - вывод справки"
	@echo "debug - собрать с опцией DEBUG, отладочный вывод"
	@echo "run   - запустить main"
	@echo "rerun - удалить всё и собрать заново"
	@echo "rune  - запустить example"
	@echo "clean - удалить все результаты компиляции"

debug: override CFLAGS += -D DEBUG
debug: all

run: main
	./main

rerun: clean main
	./main

rune: example
	./example

clean:
	$(RM) main.o rbtree.o tree_print.o example.o example main

main: main.o rbtree.o tree_print.o
	$(CC) $(CFLAGS) main.o rbtree.o tree_print.o -o main

main.o : main.c rbtree.h tree_print.h
	$(CC) $(CFLAGS) -c main.c -o main.o

rbtree.o : rbtree.c rbtree.h tree_print.h err_macro.h
	$(CC) $(CFLAGS) -c rbtree.c -o rbtree.o

tree_print.o : tree_print.c tree_print.h
	$(CC) $(CFLAGS) -c tree_print.c -o tree_print.o
	
example: example.o rbtree.o tree_print.o
	$(CC) $(CFLAGS) example.o rbtree.o tree_print.o -o example

example.o: example.c rbtree.h tree_print.h
	$(CC) $(CFLAGS) -c example.c -o example.o
