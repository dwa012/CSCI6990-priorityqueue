CC=gcc
CFLAGS=-c -Wall

all: run

run: libpq.a
	$(CC) run.c libpq.a -o run
	
libpq.a: priority_queue.o
	ar rcs libpq.a priority_queue.o
	
priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) priority_queue.c
	
#THIS NEXT SECTION IS FOR THE TEST PROGRAM
	 
test: priority_queue_test.o
	$(CC) -Igtest-1.6.0/include -Lgtest-1.6.0/lib -lpthread -lgtest -lgtest_main  priority_queue_test.o test_runner.c -o test
	
priority_queue_test.o: priority_queue.o
	$(CC) -c -Igtest-1.6.0/include -Lgtest-1.6.0/lib -lpthread -lgtest -lgtest_main priority_queue_test.c -o priority_queue_test.o
	
#FOR CLEANING ALL MADE FILES
clean:
	rm -rf *.o *~ run test libpq.a
	
