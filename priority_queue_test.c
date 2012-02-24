#include "priority_queue.c"
#include <limits.h>
#include "gtest/gtest.h"

TEST(PRIORITY,QUEUE_ENQUEUE){
	//~ QUEUE_DOES_NOT_EXIST
	//~ QUEUE_IS_FULL
	//~ TICKEN_INVLAID
	//~ ITEM_INVALID
	
	//~ item != NULL && item.item != NULL &&
	//~ item.priority != NULL && item.priority > 0
	//~ item.priority < 10. item.priority is given as
	//~ 0 is least urgent, and 10 is most urgent.
	
	
}

TEST(PRIORITY_QUEUE,DEQUEUE){
	//~ QUEUE_IS_EMPTY
    //~ QUEUE_DOES_NOT_EXIST
    //~ TOKEN_INVLAID
    RESULT result = dequeue(424234);
	EXPECT_EQ(result.code,TICKET_INVLAID);//or does not exist
	EXPECT_EQ(result.element,NULL);
	
	
	WELCOME_PACKET packet = create_queue();
	RESULT result = dequeue(packet.ticket);
	EXPECT_EQ(result.code,QUEUE_IS_EMPTY);
	EXPECT_EQ(result.element,NULL);
	
	for(int i = 1; i <= MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		ELEMENT e;
		e.item = i;
		e.priority = i;
		enqueue(e,packet.ticket);
	}
	
	for(int i = MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i >= 1; i--){
		RESULT item = dequeue(packet.ticket);
		EXPECT_EQ(item.element.item,i);
		EXPECT_EQ(item.element.priority,i);
	}
	
	RESULT result = dequeue(packet.ticket);
	EXPECT_EQ(result.code,QUEUE_IS_EMPTY);
	EXPECT_EQ(result.element,NULL);
	
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

