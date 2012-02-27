/*
 * File: priority_queue.h
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This header provides the prototypes for a priority queue library.
 * All queue operations generate an RESULT. If the operation is a
 * success then the RESULT will reflect that.
 */
 
 #ifndef STORMO_WARD_PRIORITY_QUEUE
 #define STORMO_WARD_PRIORITY_QUEUE

 #include <stdlib.h> 

 //RESULT defines
 #define SUCCESS						 1
 #define OUT_OF_MEMORY				-1
 #define TICKET_INVALID				-2
 #define ITEM_INVALID				-3
 #define QUEUE_IS_FULL				-4
 #define QUEUE_IS_NOT_FULL			-5
 #define QUEUE_IS_EMPTY				-6
 #define QUEUE_CANNOT_BE_CREATED	-7
 
 #define MAX_STRING_LENGTH			1024

 typedef unsigned int uint; 
 typedef unsigned long QUEUE_TICKET; //used for the ticket of a queue
 
 //Used for queue items to store the item with a priority
 typedef struct queue_element_struct {
 	char item[MAX_STRING_LENGTH];
 	uint priority;
 } ELEMENT;
 
 //Used for RESULT messages. Will hold an RESULT message and code
 typedef struct result{
 	char message[MAX_STRING_LENGTH];
 	int code;
 } RESULT;
 
 //Used for returning a element operation's RESULT and data returns.
 //Data is valid if the RESULT.code == SUCCESS
 typedef struct element_result{
 	ELEMENT element;
 	RESULT result;
 } ELEMENT_RESULT;
 
 //Used for returning a size operation's RESULT and data returns.
 //Data is valid if the RESULT.code == SUCCESS
 typedef struct size_result{
 	uint size;
 	RESULT result;
 } SIZE_RESULT;
 
 //Used for returning an queue creation operation's RESULT and data returns.
 //Data is valid if the RESULT.code == SUCCESS
 typedef struct queue_welcome{
	 QUEUE_TICKET ticket;
	 RESULT result;
} WELCOME_PACKET;
 

 /******************************************************
  * Creates a new priority queue to be used. 
  * 
  * If the queue is created successfully a ticket will
  * be returned. This ticket will need to be presented
  * when any queue operations are to be requested.
  *
  * PRECONDITION:
  *		There are still queues to create and allocate
  * POSTCONDITION: 
  * 	 	A welcome packet will be returned. This [packet
  * 	 	contain a RESULT. In the RESULT it will indicate
  * 	 	if the creation was a SUCCESS or some error code.
  * 
  * 	 	If the creation was a sucess then the welcome 
  * 	 	packet will contain a valid ticket to use for 
  * 		performing operations on a queue.
  * 
  *   	The created queue can only hold 1024 elements.
  * 		If more elements are added than that an error
  * 		will be returned.
  *
  * RESULT CODES:
  * 		QUEUE_CANNOT_BE_CREATED
  *		OUT_OF_MEMORY
  * 		SUCCESS
  ******************************************************/
 WELCOME_PACKET create_queue();
 
 /******************************************************
  * Deletes a queue.
  * 
  * Will attempt to delete the queue represented by the
  * given ticket.
  * 
  * PRECONDITION:
  *		ticket is valid for a created and non-deleted 
  * 		queue.
  * POSTCONDITION: 
  *		A RESULT will be returned when this operation
  * 		completes.
  * 
  * 		This RESULT will indicate if the queue that is
  * 		represented by the ticket was a SUCCESS.
  * 
  * 		The only error that this function could return,
  * 		is if the given ticket is not valid.
  * 
  * 		If the RESULT is a SUCCESS then the preivous
  * 		valid ticket that was given, will no longer be
  * 		valid.
  *
  * RESULT CODES:
  *		TICKET_INVALID
  * 		SUCCESS
  ******************************************************/
 RESULT delete_queue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Will place the given item into the queue represented
  * by the given ticket.
  * 
  * PRECONDITION:
  * 		The givne ticket be a valid ticket for a created
  * 		and non-deleted queue.
  * 
  * 		The given item is a valid item. item.item must 
  * 		be 1024 characters or less. 
  * 		The item's priority >= 0 && < 10
  *
  * POSTCONDITIONS
  * 		Will add the given item into the sorted priority 
  * 		queue that is represented by the given token, 
  * 		if the given ticket and item are both valid. The 
  * 		queue is sorted such that a higher priority 
  * 		(A > B) will be put in front of a lower one: 
  *		(A > B): A is placed before B in queue
  *
  *		Also such that if two items are of equal 
  * 		importance, they will be placed in order of 
  * 		submittance (first come first serve).
  *
  * 		A RESULT is generated which will indicate the 
  * 		outcome of the operation. If the item was placed
  * 		in the queue then the RESULT will be SUCCESS,
  * 		else a relative error code will be given.
  * 
  * RESULT CODES:
  * 		SUCCESS
  * 		QUEUE_IS_FULL
  * 		TICKET_INVALID
  * 		ITEM_INVALID
  * 		OUT_OF_MEMORY
  ******************************************************/
 RESULT enqueue(ELEMENT item, QUEUE_TICKET ticket);
 
 /******************************************************
  * Will remove the ELEMENT from the front of the queue
  * represtented by the given ticket.
  * 
  * PRECONDITION:
  * 		ticket is a valid ticket for a queue and the 
  *		queue is not empty.
  * 
  * POSTCONDITION:
  * 		Will remove and return the ELEMENT from the 
  * 		front of the queue represented by the ticket.
  * 
  * 		A RESULT is generated which will contain error 
  * 		codes and the ELEMENT returned if the RESULT's 
  * 		code is SUCCESS.
  * 
  * RESULT CODES:
  * 		SUCCESS
  * 		QUEUE_IS_EMPTY
  * 		TICKET_INVALID
  ******************************************************/
 ELEMENT_RESULT dequeue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Check if the queue is full
  * 
  * PRECONDITION:
  * 		Ticket is a valid ticket representing a queue
  * 
  * POSTCONDITION:
  * 		A RESULT is generated which will contain the 
  * 		resulting status codes for the operation.
  * 
  * 		If the queue is full, QUEUE_IS_FULL is given, 
  * 		otherwise QUEUE_IS_NOT_FULL or an error code is 
  * 		returned.
  * 
  * RESULT CODES:
  * 		TICKET_INVALID 
  * 		QUEUE_IS_FULL
  * 		QUEUE_IS_NOT_FULL
  ******************************************************/
 RESULT is_full(QUEUE_TICKET ticket);
 
 /******************************************************
  * Check if the size of the queue
  * 
  * PRECONDITION:
  * 		Ticket is a valid ticket representing a queue
  * 
  * POSTCONDITION:
  * 		A RESULT is generated which will contain the 
  * 		resulting status codes for the operation. If 
  * 		the  RESULT code is SUCCESS then the size will 
  * 		be provided.
  * 
  * 		If an error is given then the size returned will 
  * 		be 0.
  * 
  * RESULT CODES:
  * 		SUCCESS
  * 		TICKET_INVALID
  ******************************************************/
 SIZE_RESULT get_size(QUEUE_TICKET ticket);
 
#endif //STORMO_WARD_PRIORITY_QUEUE
