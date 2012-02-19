/*
 * File: priority_queue.h
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This header provides the prototypes for a priority queue library.
 */
 
 #ifndef STORMO_WARD_PRIORITY_QUEUE
 #define STORMO_WARD_PRIORITY_QUEUE
 
 
 //USED TO STORE QUEUE ELEMENTS
 typedef struct queue_element_struct {
 	int item;
 	int priority;
 } ELEMENT;
 
 typedef struct queue_error{
 	char message[1024];
 	int code;
 } ERROR;
 
 typedef long QUEUE_TICKET;
 
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
  *		the error will be given with a message and a
  *		corresponding error code.
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
  *		already deleted an error will be given. The error
  *		will contain a message and a code.
  *
  * ERROR CODES:
  *		QUEUE_CANNOT_BE_DELETED
  *		QUEUE_PREVIOUSLY_DELETED
  *		TOKEN_INVALID
  ******************************************************/
 ERROR delete_queue(QUEUE_TICKET token);
 
 /******************************************************
  * Will place the gien item into the queue specified
  * by the given token.
  * 
  * PRECONDITIONS:
  * 	item != NULL &7 item.item != NULL
  * 	item.priority != NULL.
  ******************************************************/
 void enqueue(ELEMENT item, QUEUE_TICKET token);
 
 /******************************************************
  * 
  ******************************************************/
 ELEMENT dequeue(QUEUE_TICKET token);
 
 /******************************************************
  * Get the error of the last action if any.
  ******************************************************/
 ERROR GET_LAST_ERROR(QUEUE_TICKET token);
 
 
#endif //STORMO_WARD_PRIORITY_QUEUE
