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
 #define SUCCESS					 1
 #define OUT_OF_MEMORY				-1
 #define TICKET_INVALID				-2
 #define ITEM_INVALID				-3
 #define QUEUE_IS_FULL				-4
 #define QUEUE_IS_EMPTY				-5
 #define QUEUE_CANNOT_BE_CREATED	-6

 typedef unsigned int uint; 
 typedef unsigned long QUEUE_TICKET; //used for the ticket of a queue
 
 //Used for queue items to store the item an priority
 typedef struct queue_element_struct {
 	int item;
 	uint priority;
 } ELEMENT;
 
 //Used for RESULT messages. Will hold an RESULT message and code
 typedef struct result{
 	char message[1024];
 	int code;
 } RESULT;
 
 typedef struct element_result{
 	ELEMENT element;
 	RESULT result;
 } ELEMENT_RESULT;
 
 typedef struct size_result{
 	uint size;
 	RESULT result;
 } SIZE_RESULT;
 
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
  * 	the created queue. If result > 0 then the
  * 	queue was successfully created. If result < 0
  * 	then there was an RESULT creating the queue.
  * 
  * 	The created queue can only hold 1024 elements.
  * 	If more elements are added than that then an
  * 	RESULT will be produced.
  *
  * RESULT CODES:
  * 	QUEUE_CANNOT_BE_CREATED
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
  *		ticket is a valid ticket and queue has not been
  *		been previously deleted. token != NULL.
  * POSTCONDITION: 
  *		If the ticket is valid and reperesents an existing
  *		queue, it will be deleted. If the ticket is invalid,
  *		the queue is already deleted, or the queue was
  *		already deleted an RESULT will be given. 
  * 
  * 	The RESULT will contain a message and an RESULT code.
  *
  * RESULT CODES:
  *		TICKET_INVALID
  * 	SUCCESS
  ******************************************************/
 RESULT delete_queue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Will place the gien item into the queue represented
  * by the given token.
  * 
  * PRECONDITION:
  * 	item != NULL && item.item != NULL &&
  * 	item.priority != NULL && item.priority > 0
  * 	item.priority < 10. item.priority is given as
  * 	0 is least urgent, and 10 is most urgent.
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
  * 	An RESULT will be returned that will contain a 
  * 	RESULT message and RESULT code.
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	QUEUE_IS_FULL
  * 	TICKET_INVLAID
  * 	ITEM_INVALID
  * 	ITEM_COULD_NOT_BE_ADDED
  ******************************************************/
 RESULT enqueue(ELEMENT item, QUEUE_TICKET token);
 
 /******************************************************
  * Will remove the ELEMENT from the front of the queue
  * represtented by the given token.
  * 
  * PRECONDITION:
  * 	token > 0 and be a valid token for a created
  * 	queue, token is valid for a queue that has
  * 	not been previously deleted, has been 
  * 	previously created, and is_empty() == FALSE.
  * 
  * POSTCONDITION:
  * 	Will remove and return the ELEMENT from the 
  * 	front of the queue represented by the token.
  * 
  * 	Will create an RESULT which can be retrieved
  * 	with get_last_RESULT(token). This RESULT will
  * 	contain a message and an RESULT code.
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	QUEUE_IS_EMPTY
  * 	TICKET_INVLAID
  ******************************************************/
 ELEMENT_RESULT dequeue(QUEUE_TICKET token);
 
 /******************************************************
  * Check if the queue is full
  * 
  * PRECONDITION:
  * 	token > 0 and be a valid token for a created
  * 	queue that has not been deleted.
  * 
  * POSTCONDITION:
  * 	Will return TRUE if the queue represented by
  * 	the token is full, else returns FALSE
  * 
  * RESULT CODES:
  * 	SUCCESS
  * 	TICKET_INVLAID 
  * 	QUEUE_IS_FULL
  * 	QUEUE_IS_NOT_FULL
  ******************************************************/
 RESULT is_full(QUEUE_TICKET ticket);
 

 SIZE_RESULT get_size(QUEUE_TICKET ticket);
 
#endif //STORMO_WARD_PRIORITY_QUEUE
