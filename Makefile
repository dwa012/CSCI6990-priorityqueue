CC=gcc
CFLAGS=-c -Wall

all: app lib

# CREATE THE APPLICATION
app: clean libpq.a
	$(CC) app.c libpq.a -o app

# CREATE THE LIBRARY
lib: libpq.a
	$(libpq.a)
	
libpq.a: priority_queue.o
	ar rcs libpq.a priority_queue.o
	
priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) priority_queue.c
	
#THIS NEXT SECTION IS FOR THE TEST PROGRAM
test: clean priority_queue_test.o
	g++ -Igtest-1.6.0/include -Lgtest-1.6.0/lib priority_queue_test.o gtest-1.6.0/src/gtest_main.cc -o test -lpthread -lgtest

priority_queue_test.o:
	g++ -w -c -Igtest-1.6.0/include -o priority_queue_test.o priority_queue_test.c
	
.PHONY: clean all
	
#FOR CLEANING ALL MADE FILES
clean:
	rm -rf *.o *~ run test libpq.a
	
	
	
