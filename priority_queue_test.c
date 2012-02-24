#include "priority_queue.c"
#include <limits.h>
#include "gtest/gtest.h"

/******************************************************
  * Creates a new priority queue to be used. 
  * 
  * If the queue is created successfully a token will
  * be returned. This token will need to be presented
  * when any queue operations are to be requested.
  *
  * PRECONDITION:
  *		
  * POSTCONDITION: 
  *		The returned value will be the identifier for
  * 	the created queue. If result > 0 then the
  * 	queue was successfully created. If result < 0
  * 	then there was an error creating the queue.
  * 
  * 	The created queue can only hold 1024 elements.
  * 	If more elements are added than that then an
  * 	ERROR will be produced.
  *
  * ERROR CODES:
  ******************************************************/
 //QUEUE_TICKET create_queue();
 
 //TEST(PRIORITY_QUEUE,CREATE){
	 
 //}
 
 /******************************************************
  * Deletes a queue.
  * 
  * Will attempt to delete the queue represented by the
  * given token.
  * 
  * PRECONDITION:
  *		token is a valid token and queue has not been
  *		been previously deleted. token != NULL.
  * POSTCONDITION: 
  *		If the token is valid and reperesents an existing
  *		queue, it will be deleted. If the token is invalid,
  *		the queue is already deleted, or the queue was
  *		already deleted an ERROR will be given. 
  * 
  * 	The ERROR will contain a message and an error code.
  *
  * ERROR CODES:
  *		QUEUE_CANNOT_BE_DELETED
  *		QUEUE_PREVIOUSLY_DELETED
  *		TOKEN_INVALID
  ******************************************************/
 //ERROR delete_queue(QUEUE_TICKET token);
 
 /******************************************************
  * Will place the gien item into the queue represented
  * by the given token.
  * 
  * PRECONDITION:
  * 	item != NULL && item.item != NULL &&
  * 	item.priority != NULL && item.priority > 0
  * 	item.priority < 1,000,000
  * 	
  * 	token > 0 and be a valid token for a created
  * 	queue, queue that has not been previously deleted,
  * 	a queue that is not full.
  * 
  * POSTCONDITIONS
  * 	Will add the given item to the end of the queue
  * 	that is represented by the given token, iff the
  * 	given token is valid and the item is valid.
  * 
  * 	An ERROR will be returned that will contain a 
  * 	error message and error code.
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_IS_FULL
  * 	TOKEN_INVLAID
  * 	ITEM_INVALID
  ******************************************************/
 //ERROR enqueue(ELEMENT item, QUEUE_TICKET token);

TEST(PRIORITY_QUEUE,DEQUEUE){
	//~ QUEUE_IS_EMPTY
    //~ QUEUE_DOES_NOT_EXIST
    //~ TOKEN_INVLAID
    RESULT result = dequeue(424234);
	EXPECT_EQ(result.code,TICKET_INVLAID);
	EXPECT_EQ(result.element,NULL);
	
	
	WELCOME_PACKET packet = create_queue();
	RESULT result = dequeue(packet.ticket);
	EXPECT_EQ(result.code,QUEUE_IS_EMPTY);
	EXPECT_EQ(result.element,NULL);
	
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		ELEMENT e;
		e.item = i;
		e.priority = i;
		enqueue(e,packet.ticket);
	}
	
	
    
}
 
TEST(PRIORITY_QUEUE,FULL){
	//~ QUEUE_DOES_NOT_EXIST
	//~ TOKEN_INVLAID 
	//~ QUEUE_IS_FULL
	//~ QUEUE_IS_NOT_FULL
	
	//try to get the full status of a non existent queue
	RESULT result = is_full(424234);
	EXPECT_EQ(result.code,TOKEN_INVLAID);
	
	//fill up the queue
	WELCOME_PACKET packet = create_queue();
	
	if(packet.result.code == SUCCESS){
		for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE-1; i++){
			ELEMENT e;
			e.item = i;
			e.priority = i;
			enqueue(e,packet.ticket);
			EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_NOT_FULL);
		}
		
		ELEMENT e;
		e.item = 3;
		e.priority = 2331;
		
		enqueue(e,packet.ticket);
		EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
		
		enqueue(e,packet.ticket);
		EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
		
		enqueue(e,packet.ticket);
		EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
		
	}
	//done filling up queue
	
	//delete the queue then try to get the full status
	delete_queue(packet.ticket);
	EXPECT_EQ(is_full(packet.ticket).code,QUEUE_DOES_NOT_EXIST);
	
}

