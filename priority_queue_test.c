 /*
 * File: priority_queue_test.c
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This is a test program for the priority_queue.c file.
 * 
 * This test progrma uses the Google C++ Framework.
 * It requires those libraries to work. Since the 
 * framework is in C++, there are a few C++ syntax elements
 * in this program.
 * 
 * You will have to use g++ or an equivalent to compile this
 * program.
 */
 
#include "priority_queue.c"
#include <limits.h>
#include "gtest/gtest.h"

#include <stdlib.h>
#include <time.h>

static ELEMENT fill_element(char * message, int priority);

TEST(PRIORITY_QUEUE,CREATE_QUEUE){
	
	WELCOME_PACKET w = create_queue();
	delete_queue(w.ticket);
	WELCOME_PACKET wp[1024];
	
	//this is used to stress test the creation and deletion of queues.
	for(int m = 0; m < 1000; m++){

		for(int j = 0; j < 100; j++){
			
			for(int i = 0; i < MAXIMUM_NUMBER_OF_QUEUES ; i++){
				wp[i] = create_queue();
				EXPECT_EQ(wp[i].result.code, SUCCESS);
			}
			
			for(int i = 0; i < MAXIMUM_NUMBER_OF_QUEUES ; i++)
				EXPECT_EQ(delete_queue(wp[i].ticket).code, SUCCESS);
		}	
		
		for(int i = 0; i < MAXIMUM_NUMBER_OF_QUEUES ; i++)
			EXPECT_EQ(delete_queue(wp[i].ticket).code,TICKET_INVALID);
	}//end creation stress test
		
	//create a full set of queues
	for(int i = 0; i < MAXIMUM_NUMBER_OF_QUEUES ; i++){
		wp[i] = create_queue();
		EXPECT_EQ(wp[i].result.code, SUCCESS);
	}
	
	//delete some random queues and try to recreate them
	delete_queue(wp[0].ticket);
	delete_queue(wp[1023].ticket);
	delete_queue(wp[64].ticket);
	delete_queue(wp[800].ticket);
	
	wp[0] = create_queue();
	EXPECT_EQ(wp[0].result.code,SUCCESS);
	
	wp[1023] = create_queue();
	EXPECT_EQ(wp[1023].result.code,SUCCESS);
	
	wp[64] = create_queue();
	EXPECT_EQ(wp[64].result.code,SUCCESS);
	
	wp[800] = create_queue();
	EXPECT_EQ(wp[800].result.code,SUCCESS);
	
	//delete all created queues
	for(int i = 0; i < MAXIMUM_NUMBER_OF_QUEUES ; i++)
		delete_queue(wp[i].ticket);
}

TEST(PRIORITY_QUEUE,DELETE_QUEUE){
	
	//try to delete a queue with a forged ticket
	RESULT r = delete_queue(23131323);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
	WELCOME_PACKET w = create_queue();
	EXPECT_EQ(w.result.code, SUCCESS);
	
	//delete a queue with a valid ticket
	r = delete_queue(w.ticket);
	EXPECT_EQ(r.code, SUCCESS);
	
	//try to delete an already deleted queue
	r = delete_queue(w.ticket);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
}

TEST(PRIORITY_QUEUE,ENQUEUE){
	
	//try a bad ticket numbers
	ELEMENT e = {"test",9};
	
	RESULT r = enqueue(e,-313213);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
	r = enqueue(e,0);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
	//create a valid queue
	WELCOME_PACKET packet = create_queue();
		
	//try bad priority
	e = fill_element("test",-3);
	
	r = enqueue(e,packet.ticket);
	EXPECT_EQ(r.code, ITEM_INVALID);
	
	//try bad priority
	e = fill_element("test",11);
	
	r = enqueue(e,packet.ticket);
	EXPECT_EQ(r.code, ITEM_INVALID);
	//fill queue	
	e = fill_element("test",4);
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		r = enqueue(e,packet.ticket);
		EXPECT_EQ(get_size(packet.ticket).size,i+1);
		EXPECT_EQ(r.code, SUCCESS);
	}

	//add one to many to the queue
	r = enqueue(e,packet.ticket);
	EXPECT_EQ(r.code, QUEUE_IS_FULL);

	//delete the queue
	r = delete_queue(packet.ticket);
	EXPECT_EQ(r.code,SUCCESS);
	
	//try to enque on a deleted queue
	r = enqueue(e,packet.ticket);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
	///////////////////////////////////////////////////////////
	// CHECK FOR THE CORRECT ENQUEUEUING BASED ON PRIORITIES //
	
	srand(time(NULL));
	
	packet = create_queue();

	// fill queue with max elements with random priorities from
	// [0-10], then compare the insertion number as the base of the
	// comparision
	char temp[1024];
	
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		snprintf(temp,1024,"%d",i);
		e = fill_element(temp,rand()%10);
		r = enqueue(e,packet.ticket);
		EXPECT_EQ(get_size(packet.ticket).size,i+1);
		EXPECT_EQ(r.code, SUCCESS);
	}
	
	ELEMENT_RESULT er;
	ELEMENT_RESULT last;
	
	last = dequeue(packet.ticket);
	
	for(int i = 1; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){		
		er = dequeue(packet.ticket);
		EXPECT_TRUE(last.element.priority >= er.element.priority);
		
		if(last.element.priority == er.element.priority)
			EXPECT_TRUE(atoi(last.element.item) < atoi(er.element.item));
		
		last = er;
	}
	
	
}

TEST(PRIORITY_QUEUE,DEQUEUE){
    ELEMENT_RESULT ele_result = dequeue(424234);
	EXPECT_EQ(ele_result.result.code,TICKET_INVALID);//or does not exist
	EXPECT_EQ(strcmp(ele_result.element.item,""),0);
	EXPECT_EQ(ele_result.element.priority,0);
	
	
	WELCOME_PACKET packet = create_queue();
	ele_result = dequeue(packet.ticket);
	EXPECT_EQ(ele_result.result.code,QUEUE_IS_EMPTY);
	
	ELEMENT e;
	char temp[MAX_STRING_LENGTH];
	
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		snprintf(temp,MAX_STRING_LENGTH,"%d",i);
		e = fill_element(temp,4);
		enqueue(e,packet.ticket);
	}
	
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		ELEMENT_RESULT item = dequeue(packet.ticket);
		e = item.element;
		snprintf(temp,MAX_STRING_LENGTH,"%d",i);
		EXPECT_EQ(strcmp(e.item,temp),0);
	}
	
	ELEMENT_RESULT r = dequeue(packet.ticket);
	EXPECT_EQ(r.result.code,QUEUE_IS_EMPTY);
	
	RESULT res = delete_queue(packet.ticket);
	EXPECT_EQ(res.code,SUCCESS);
	
	ELEMENT_RESULT result = dequeue(packet.ticket);
	EXPECT_EQ(r.result.code,QUEUE_IS_EMPTY);
}
 
TEST(PRIORITY_QUEUE,FULL){
	
	//try to get the full status of a non existent queue
	RESULT result = is_full(424234);
	EXPECT_EQ(result.code,TICKET_INVALID);
	
	//fill up the queue
	WELCOME_PACKET packet = create_queue();
	
	//if(packet.result.code == SUCCESS){
		
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE-1; i++){
		ELEMENT e = {i,i%10};
		EXPECT_EQ(enqueue(e,packet.ticket).code,SUCCESS);
		EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_NOT_FULL);
	}
	
	ELEMENT e = {3,3};		
	enqueue(e,packet.ticket);
	
	EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
	
	enqueue(e,packet.ticket);
	EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
	

	enqueue(e,packet.ticket);
	EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
	
	//delete the queue then try to get the full status
	delete_queue(packet.ticket);
	EXPECT_EQ(is_full(packet.ticket).code,TICKET_INVALID);
	
}

TEST(PRIORITY_QUEUE,GET_SIZE){
	SIZE_RESULT sr;
	ELEMENT e = {"test",4};
	WELCOME_PACKET wp = create_queue();
	
	sr = get_size(wp.ticket);
	EXPECT_EQ(sr.size,0);
	
	for(int i = 1; i <= MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		enqueue(e,wp.ticket);
		EXPECT_EQ(get_size(wp.ticket).size, i);
	}
	
	for(int i = MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i > 0; i--){
		dequeue(wp.ticket);
		EXPECT_EQ(get_size(wp.ticket).size, i-1);
	}
	
}

static ELEMENT fill_element(char * message, int priority){
	ELEMENT e;
	snprintf(e.item,MAX_STRING_LENGTH,"%s",message);
	e.priority = priority;
	return e;
}
