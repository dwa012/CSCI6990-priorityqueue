CC=gcc
CFLAGS=-c -Wall

all: run lib test

run: libpq.a
	$(CC) run.c libpq.a -o run
	
lib: libpq.a
	$(libpq.a)
	
libpq.a: priority_queue.o
	ar rcs libpq.a priority_queue.o
	
priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) priority_queue.c
	
#THIS NEXT SECTION IS FOR THE TEST PROGRAM
test: priority_queue_test.o
	g++ -Igtest-1.6.0/include -Lgtest-1.6.0/lib priority_queue_test.o gtest-1.6.0/src/gtest_main.cc -o test -lpthread -lgtest

priority_queue_test.o:
	g++ -c -Igtest-1.6.0/include -o priority_queue_test.o priority_queue_test.c
	
.PHONY: all clean test
	
#FOR CLEANING ALL MADE FILES
clean:
	rm -rf *.o *~ run test libpq.a
	
