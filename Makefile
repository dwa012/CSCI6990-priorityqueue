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
	 
#test: priority_queue_test.o
	#g++ -Igtest-1.6.0/include -Lgtest-1.6.0/lib -lpthread -lgtest -lgtest_main  priority_queue_test.o test_runner.c -o test
	
#test: priority_queue_test.o
#	g++ -Igtest-1.6.0/include -Lgtest-1.6.0/lib -lpthread -lgtest  test_runner.c priority_queue_test.o -o test
	
#priority_queue_test.o: libpq.a
test: libpq.a
	g++ -I./gtest-1.6.0/include -L./gtest-1.6.0/lib -lpthread -lgtest -DGTEST_HAS_PTHREAD=1 -o test priority_queue_test.c
	
#FOR CLEANING ALL MADE FILES
clean:
	rm -rf *.o *~ run test libpq.a
	
