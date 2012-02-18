# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-std=c99 -c -Wall

all: run

hello: run.o priority_queue.o
	$(CC) run.o priority_queue.o -o run
	
run.o: run.c
	$(CC) $(CFLAGS) run.c
	
priority_queue.o: priority_queue.c
	$(CC) $(CFLAGS) priority_queue.c





#clean:
#	rm -rf *o hello
