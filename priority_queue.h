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
  *		
  * POSTCONDITION: 
  *		The returned value will be the identifier for
  * 	the created queue. If result == SUCCESS then the
  * 	queue was successfully created. If result < 0
  * 	then there was an RESULT creating the queue.
  * 
  * 	The created queue can only hold 1024 elements.
  * 	If more elements are added than that then
  * 	RESULT will contain error information.
  *
  * RESULT CODES:
  * 	QUEUE_CANNOT_BE_CREATED
  *	OUT_OF_MEMORY
  * 	SUCCESS
  ******************************************************/
 WELCOME_PACKET create_queue();
 
 /******************************************************
  * Deletes a queue.
  * 
  * Will attempt to delete the queue represented by the
  * given ticket.
  * 
  * PRECONDITION:
  *		ticket is valid
  * POSTCONDITION: 
  *		If the ticket is valid and reperesents an existing
  *		queue, it will be deleted. The ticket is then invalidated
  *		and RESULT will contain code SUCCESS. 
  *		If the ticket is invalid, RESULT will contain error
  *		codes. 
  *
  * RESULT CODES:
  *	TICKET_INVALID
  * 	SUCCESS
  ******************************************************/
 RESULT delete_queue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Will place the given item into the queue represented
  * by the given ticket.
  * 
  * PRECONDITION:
  * 	item is a valid item such that it has a priority:
  * 	item.priority < 10   and  item.priority >= 0
  *	The queue represented by the ticket must also not 
  *	be full.
  *
  * POSTCONDITIONS
  * 	Will add the given item into the sorted priority queue
  * 	that is represented by the given token, if the
  * 	given ticket and item are both valid. The queue is sorted
  *	such that a higher priority (A > B) will be put infront of
  *	a lower one: 
  *	(A>B): A is placed before B in queue
  *
  *	Also such that if two items are of equal importance,
  *	they will be placed in order of submittance 
  *	(first come first serve).
  *
  * 	A RESULT is generated which will contain any error codes.
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	QUEUE_IS_FULL
  * 	TICKET_INVALID
  * 	ITEM_INVALID
  * 	OUT_OF_MEMORY
  ******************************************************/
 RESULT enqueue(ELEMENT item, QUEUE_TICKET ticket);
 
 /******************************************************
  * Will remove the ELEMENT from the front of the queue
  * represtented by the given ticket.
  * 
  * PRECONDITION:
  * 	ticket is a valid ticket for a queue and the 
  *	queue is not empty.
  * 
  * POSTCONDITION:
  * 	Will remove and return the ELEMENT from the 
  * 	front of the queue represented by the ticket.
  * 
  * 	A RESULT is generated which will contain error codes
  *	and the ELEMENT returned if the RESULT's code is
  *	SUCCESS
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	QUEUE_IS_EMPTY
  * 	TICKET_INVALID
  ******************************************************/
 ELEMENT_RESULT dequeue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Check if the queue is full
  * 
  * PRECONDITION:
  * 	Ticket is a valid ticket representing a queue
  * 
  * POSTCONDITION:
  * 	A RESULT is generated which will contain the resulting
  *	status codes for the operation.
  * 	If the queue is full, QUEUE_IS_FULL is given, otherwise
  *	QUEUE_IS_NOT_FULL or an error code is returned
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	TICKET_INVALID 
  * 	QUEUE_IS_FULL
  * 	QUEUE_IS_NOT_FULL
  ******************************************************/
 RESULT is_full(QUEUE_TICKET ticket);
 
 /******************************************************
  * Check if the size of the queue
  * 
  * PRECONDITION:

  * 	Ticket is a valid ticket representing a queue
  * 
  * POSTCONDITION:
  * 	A RESULT is generated which will contain the resulting
  *	status codes for the operation. If the RESULT code is
  *	SUCCESS then the data supplied is valid
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	TICKET_INVALID
  ******************************************************/
 SIZE_RESULT get_size(QUEUE_TICKET ticket);
 
#endif //STORMO_WARD_PRIORITY_QUEUE
