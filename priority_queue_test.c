#include "priority_queue.h"
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
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	QUEUE_IS_FULL
  * 	TOKEN_INVLAID
  * 	ITEM_INVALID
  ******************************************************/
 //ERROR enqueue(ELEMENT item, QUEUE_TICKET token);
 
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
 //ELEMENT dequeue(QUEUE_TICKET token);
 
 /******************************************************
  * Get the error if any of the last action if any.
  * 
  * Will return the last error for the queue represented
  * by the token.
  *
  * PRECONDITION:
  * 	token > 0 and be a valid token for a created
  * 	queue that has not been deleted.
  * 
  * POSTCONDITION:
  * 	Will return an ERROR that will contain the
  * 	message and error code of the last operation
  * 	on the queue represtned by the given token.
  * 	If no error occured then the ERROR code will
  * 	be SUCCESS and the message will be empty.
  ******************************************************/
 //ERROR get_last_error(QUEUE_TICKET token);

 /******************************************************
  * Check if the queue is empty
  * 
  * PRECONDITION:
  * 	token > 0 and be a valid token for a created
  * 	queue that has not been deleted.
  * 
  * POSTCONDITION:
  * 	Will return TRUE if the queue represented by
  * 	the token is full, else returns FALSE 
  * 
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TOKEN_INVLAID
  ******************************************************/
 //bool is_empty(QUEUE_TICKET token);
 
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
  * ERROR CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TOKEN_INVLAID 
  ******************************************************/
 //bool is_full(QUEUE_TICKET token);
//TEST(PRIORITY_QUEUE,CREATE){
	
//}
