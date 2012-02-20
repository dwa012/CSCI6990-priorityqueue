/*
 * File: priority_queue.h
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This header provides the prototypes for a priority queue library.
 * All queue operations generate an ERROR. If the operation is a
 * success then the ERROR will reflect that.
 */
 
 #ifndef STORMO_WARD_PRIORITY_QUEUE
 #define STORMO_WARD_PRIORITY_QUEUE
 
 //Defines for the typedefed bool
 #define TRUE 1
 #define FALSE 0
 
 //error defines
 #define QUEUE_CANNOT_BE_DELETED	-1
 #define QUEUE_PREVIOUSLY_DELETED	-2
 #define TICKET_INVALID				-3
 #define QUEUE_DOES_NOT_EXIST		-4
 #define QUEUE_IS_FULL				-5
 #define ITEM_INVALID				-6
 #define QUEUE_IS_EMPTY				-7
 
 typedef long QUEUE_TICKET; //used for the ticket of a queue
 typedef char bool; //a stand in type for a bool
 
 //Used for queue items to store the item an priority
 typedef struct queue_element_struct {
 	int item;
 	int priority;
 } ELEMENT;
 
 //Used for error messages. Will hold an error message and code
 typedef struct queue_error{
 	char message[1024];
 	int code;
 } ERROR;
 

 
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
  * 	then there was an error creating the queue.
  *
  * ERROR CODES:
  ******************************************************/
 QUEUE_TICKET create_queue();
 
 /******************************************************
  * Deletes a queue.
  * 
  * Will attempt to delete the queue represented by the
  * given ticket.
  * 
  * PRECONDITION:
  *		ticket is a valid ticket and queue has not been
  *		been previously deleted. ticket != NULL.
  * POSTCONDITION: 
  *		If the ticket is valid and reperesents an existing
  *		queue, it will be deleted. If the ticket is invalid,
  *		the queue is already deleted, or the queue was
  *		already deleted an ERROR will be given. 
  * 
  * 	The ERROR will contain a message and an error code.
  *
  * ERROR CODES:
  *		QUEUE_CANNOT_BE_DELETED
  *		QUEUE_PREVIOUSLY_DELETED
  *		TICKET_INVALID
  ******************************************************/
 ERROR delete_queue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Will place the gien item into the queue represented
  * by the given ticket.
  * 
  * PRECONDITION:
  * 	item != NULL && item.item != NULL &&
  * 	item.priority != NULL && item.priority > 0
  * 	item.priority < 1,000,000
  * 	
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue, queue that has not been previously deleted,
  * 	a queue that is not full.
  * 
  * POSTCONDITIONS
  * 	Will add the given item to the end of the queue
  * 	that is represented by the given ticket, iff the
  * 	given ticket is valid and the item is valid.
  * 
  * 	An ERROR will be returned that will contain a 
  * 	error message and error code.
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	QUEUE_IS_FULL
  * 	TICKET_INVLAID
  * 	ITEM_INVALID
  ******************************************************/
 ERROR enqueue(ELEMENT item, QUEUE_TICKET ticket);
 
 /******************************************************
  * Will remove the ELEMENT from the front of the queue
  * represtented by the given ticket.
  * 
  * PRECONDITION:
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue, ticket is valid for a queue that has
  * 	not been previously deleted, has been 
  * 	previously created, and is_empty() == FALSE.
  * 
  * POSTCONDITION:
  * 	Will remove and return the ELEMENT from the 
  * 	front of the queue represented by the ticket.
  * 
  * 	Will create an ERROR which can be retrieved
  * 	with get_last_error(ticket). This ERROR will
  * 	contain a message and an error code.
  * 
  * ERROR CODES:
  * 	QUEUE_IS_EMPTY
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID
  ******************************************************/
 ELEMENT dequeue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Will return a copy of the ELEMENT from the front
  * of the queue represented by the given ticket.
  * 
  * PRECONDITION:
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue, has not been previously deleted, and 
  * 	is_empty() == FALSE.
  * 
  * POSTCONDITION:
  * 	Will return a copy of the ELEMENT from the front
  * 	of the queue represented by the ticket.
  * 
  * 	Will create an ERROR which can be retrieved
  * 	with get_last_error(ticket). This ERROR will
  * 	contain a message and an error code.
  * 
  * ERROR CODES:
  * 	QUEUE_IS_EMPTY
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID
  ******************************************************/
 ELEMENT peek(QUEUE_TICKET ticket);
 
 /******************************************************
  * Check if the queue is empty
  * 
  * PRECONDITION:
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue that has not been deleted.
  * 
  * POSTCONDITION:
  * 	Will return TRUE if the queue represented by
  * 	the ticket is full, else returns FALSE 
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID
  ******************************************************/
 bool is_empty(QUEUE_TICKET ticket);
 
 /******************************************************
  * Check if the queue is full
  * 
  * PRECONDITION:
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue that has not been deleted.
  * 
  * POSTCONDITION:
  * 	Will return TRUE if the queue represented by
  * 	the ticket is full, else returns FALSE
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID 
  ******************************************************/
 bool is_full(QUEUE_TICKET ticket);
 
 /******************************************************
  * Get the error if any of the last action if any.
  * 
  * Will return the last error for the queue represented
  * by the ticket.
  *
  * PRECONDITION:
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue that has not been deleted.
  * 
  * POSTCONDITION:
  * 	Will return an ERROR that will contain the
  * 	message and error code of the last operation
  * 	on the queue represtned by the given ticket.
  * 	If no error occured then the ERROR code will
  * 	be SUCCESS and the message will be empty.
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID 
  ******************************************************/
 ERROR get_last_error(QUEUE_TICKET ticket);
 
#endif //STORMO_WARD_PRIORITY_QUEUE
