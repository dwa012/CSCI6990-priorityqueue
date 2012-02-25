#include "priority_queue.c"
#include <limits.h>
#include "gtest/gtest.h"

TEST(PRIORITY,CREATE_QUEUE){
	//~ QUEUE_CANNOT_BE_CREATED
	//~ SUCCESS
	WELCOME_PACKET w = create_queue();
	EXPECT_EQ(w.result.code, SUCCESS);
	
	WELCOME_PACKET wp[1023];
	
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE-1; i++){
		wp[i] = create_queue();
		EXPECT_EQ(wp[i].result.code, SUCCESS);
	}
	
	WELCOME_PACKET p = create_queue();
	EXPECT_EQ(p.result.code,QUEUE_CANNOT_BE_CREATED);
	
	//delete all created queues
	delete_queue(w.ticket);
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE-1; i++)
		delete_queue(wp[i].ticket);
		
	//create a full set of queues
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		wp[i] = create_queue();
		EXPECT_EQ(wp[i].result.code, SUCCESS);
	}
	
	//delete some random queues and try to recreate them
	delete_queue(wp[0]);
	delete_queue(wp[1024]);
	delete_queue(wp[64]);
	delete_queue(wp[800]);
	
	wp[0] = create_queue();
	EXPECT_EQ(wp[0].result.code,SUCCESS);
	
	wp[1024] = create_queue();
	EXPECT_EQ(wp[1024].result.code,SUCCESS);
	
	wp[64] = create_queue();
	EXPECT_EQ(wp[64].result.code,SUCCESS);
	
	wp[800] = create_queue();
	EXPECT_EQ(wp[800].result.code,SUCCESS);
	
	//delete all created queues
	delete_queue(w.ticket);
	for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE-1; i++)
		delete_queue(wp[i].ticket);
}

TEST(PRIORITY,DELETE_QUEUE){
	//~ TICKET_INVALID
	
	//try to delete a queue with a forged ticket
	RESULT r = delete_queue(23131323);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
	WELCOME_PACKET w = create_queue();
	
	//delete a queue with a valid ticket
	r = delete_queue(w.ticket);
	EXPECT_EQ(r.code, SUCCESS);
	
	//try to delete an already deleted queue
	r = delete_queue(w.ticket);
	EXPECT_EQ(r.code, TICKET_INVALID);
	
}

//TEST(PRIORITY,QUEUE_ENQUEUE){
	////~ QUEUE_DOES_NOT_EXIST
	////~ QUEUE_IS_FULL
	////~ TICKEN_INVLAID
	////~ ITEM_INVALID
	
	////~ item != NULL && item.item != NULL &&
	////~ item.priority != NULL && item.priority > 0
	////~ item.priority < 10. item.priority is given as
	////~ 0 is least urgent, and 10 is most urgent.
	
	////try a bad ticket numbers
	//ELEMENT e = {8,9};
	
	//RESULT r = enqueue(e,-313213);
	//EXPECT_EQ(r.code, TICKET_INVALID);
	
	//r = enqueue(e,0);
	//EXPECT_EQ(r.code, TICKET_INVALID);
	
	////create a valid queue
	//WELCOME_PACKET packet = create_queue();
	
	////~ //try NULL item and priority
	////~ e = {NULL,NULL};
	////~ 
	////~ r = enqueue(e,packet.ticket);
	////~ EXPECT_EQ(r.code, ITEM_INVALID);
	
	////try bad priority
	//e = {3,-1};
	
	//r = enqueue(e,packet.ticket);
	//EXPECT_EQ(r.code, ITEM_INVALID);
	
	////try bad priority
	//e = {3,11};
	
	//r = enqueue(e,packet.ticket);
	//EXPECT_EQ(r.code, ITEM_INVALID);
	
	////fill queue	
	//e = {2,4};
	//for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		//r = enqueue(e,packet.ticket);
		//EXPECT_EQ(r.code, SUCCESS);
	//}
	
	////add one to many to the queue
	//r = enqueue(e,packet.ticket);
	//EXPECT_EQ(r.code, QUEUE_IS_FULL);
	
	////delete the queue
	//r = delete_queue(packet.ticket);
	//EXPECT_EQ(r.code,SUCCESS);
	
	////try to enque on a deleted queue
	//r = enqueue(e,packet.ticket);
	//EXPECT_EQ(r.code, QUEUE_DOES_NOT_EXIST);
	
	
//}

//TEST(PRIORITY_QUEUE,DEQUEUE){
	////~ QUEUE_IS_EMPTY
    ////~ QUEUE_DOES_NOT_EXIST
    ////~ TOKEN_INVLAID
    //ELEMENT_RESULT ele_result = dequeue(424234);
	//EXPECT_EQ(ele_result.result.code,TICKET_INVLAID);//or does not exist
	//EXPECT_EQ(ele_result.element,NULL);
	
	
	//WELCOME_PACKET packet = create_queue();
	//ele_result = dequeue(packet.ticket);
	//EXPECT_EQ(ele_result.result.code,QUEUE_IS_EMPTY);
	
	//for(int i = 1; i <= MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i++){
		//ELEMENT e;
		//e.item = i;
		//e.priority = i;
		//enqueue(e,packet.ticket);
	//}
	
	//for(int i = MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE; i >= 1; i--){
		//ELEMENT_RESULT item = dequeue(packet.ticket);
		//EXPECT_EQ(item.element.item,i);
		//EXPECT_EQ(item.element.priority,i);
	//}
	
	//ELEMENT_RESULT result = dequeue(packet.ticket);
	//EXPECT_EQ(result.code,QUEUE_IS_EMPTY);
	
	//result = delete_queue(packet.ticket);
	//EXPECT_EQ(result.code,SUCCESS);
	
	//ELEMENT_RESULT result = dequeue(packet.ticket);
	//EXPECT_EQ(result.code,QUEUE_IS_EMPTY);
//}
 
//TEST(PRIORITY_QUEUE,FULL){
	////~ QUEUE_DOES_NOT_EXIST
	////~ TOKEN_INVLAID 
	////~ QUEUE_IS_FULL
	////~ QUEUE_IS_NOT_FULL
	
	////try to get the full status of a non existent queue
	//RESULT result = is_full(424234);
	//EXPECT_EQ(result.code,TOKEN_INVLAID);
	
	////fill up the queue
	//WELCOME_PACKET packet = create_queue();
	
	//if(packet.result.code == SUCCESS){
		//for(int i = 0; i < MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE-1; i++){
			//ELEMENT e;
			//e.item = i;
			//e.priority = i;
			//enqueue(e,packet.ticket);
			//EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_NOT_FULL);
		//}
		
		//ELEMENT e;
		//e.item = 3;
		//e.priority = 2331;
		
		//enqueue(e,packet.ticket);
		//EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
		
		//enqueue(e,packet.ticket);
		//EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
		
		//enqueue(e,packet.ticket);
		//EXPECT_EQ(is_full(packet.ticket).code,QUEUE_IS_FULL);
		
	//}
	////done filling up queue
	
	////delete the queue then try to get the full status
	//delete_queue(packet.ticket);
	//EXPECT_EQ(is_full(packet.ticket).code,QUEUE_DOES_NOT_EXIST);
	
//}

