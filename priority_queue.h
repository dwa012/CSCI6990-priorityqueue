/*
 * File: priority_queue.h
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This header provides the prototypes for a priority queue library.
 */
 
 #ifndef STORMO_WARD_PRIORITY_QUEUE
 #define STORMO_WARD_PRIORITY_QUEUE
 
 //Defines for the typedefed bool
 #define TRUE 1
 #define FALSE 0
 
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
  * If the queue is created successfully a token will
  * be returned. This token will need to be presented
  * when any queue operations are to be requested.
  *
  * PRECONDITIONS:
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
  * given token.
  * 
  * PRECONDITIONS:
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
 ERROR delete_queue(QUEUE_TICKET token);
 
 /******************************************************
  * Will place the gien item into the queue represented
  * by the given token.
  * 
  * PRECONDITIONS:
  * 	item != NULL && item.item != NULL &&
  * 	item.priority != NULL && item.priority > 0
  * 	item.priority < 1,000,000
  * 	
  * 	token > 0 and be a valid token for a created
  * 	queue, queue that has not been previously deleted,
  * 	a queue that is not full.
  * 
  * POSTCONDITIONS:
  * 	Will add the given item to the end of the queue
  * 	that is represented by the given token, iff the
  * 	given token is valid and the item is valid.
  * 
  * 	An ERROR will be returned that will contain a 
  * 	error message and error code.
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	QUEUE_IS_FULL
  * 	TOKEN_INVLAID
  * 	ITEM_INVALID
  ******************************************************/
 ERROR enqueue(ELEMENT item, QUEUE_TICKET token);
 
 /******************************************************
  * Will remove the ELEMENT from the front of the queue
  * represtented by the given token.
  * 
  * PRECONDITIONS:
  * 	token > 0 and be a valid token for a created
  * 	queue, token is valid for a queue that has
  * 	not been previously deleted, has been 
  * 	previously created, and is_empty() == FALSE.
  * 
  * POSTCONDITIONS:
  * 	Will remove and return the ELEMENT from the 
  * 	front of the queue represented by the token.
  * 
  * 	Will create an ERROR which can be retrieved
  * 	with get_last_error(token). This ERROR will
  * 	contain a message and an error code.
  * 
  * ERROR CODES:
  * 	QUEUE_IS_EMPTY
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TOKEN_INVLAID
  ******************************************************/
 ELEMENT dequeue(QUEUE_TICKET token);
 
 /******************************************************
  * Get the error if any of the last action if any.
  ******************************************************/
 ERROR get_last_error(QUEUE_TICKET token);

 /******************************************************
  * Check if the queue is empty
  ******************************************************/
 bool is_empty(QUEUE_TICKET token);
 
 /******************************************************
  * Check if the queue is full
  ******************************************************/
 bool is_full(QUEUE_TICKET token);
 
#endif //STORMO_WARD_PRIORITY_QUEUE
