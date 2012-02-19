CC=gcc
CFLAGS=-c -Wall

all: run

run: libpq.a
	$(CC) run.c libpq.a -o run
	
libpq.a: priority_queue.o
	ar rcs libpq.a priority_queue.o
	
priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) priority_queue.c

clean:
	rm -rf *.o *~ run libpq.a
	
