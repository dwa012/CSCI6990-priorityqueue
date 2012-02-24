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
 
 //Defines for the typedefed bool
 //#define TRUE 1
 //#define FALSE 0
 
 //RESULT defines
 #define SUCCESS					 1
 #define QUEUE_CANNOT_BE_DELETED	-1
<<<<<<< HEAD
 #define QUEUE_PREVIOUSLY_DELETED	-2
 #define TICKET_INVALID				-3
=======
 #define TOKEN_INVALID				-3
>>>>>>> 0b6ac1829effff96c624860c86ddbfe3a7e0178f
 #define QUEUE_DOES_NOT_EXIST		-4
 #define QUEUE_IS_FULL				-5
 #define QUEUE_IS_NOT_FULL			-6
 #define ITEM_INVALID				-7
 #define QUEUE_IS_EMPTY				-8
 #define QUEUE_CANNOT_BE_CREATED	-9
 
 typedef long QUEUE_TICKET; //used for the ticket of a queue
 //typedef char boolean; //a stand in type for a bool
 
 //Used for queue items to store the item an priority
 typedef struct queue_element_struct {
 	int item;
 	int priority;
 } ELEMENT;
 
 //Used for RESULT messages. Will hold an RESULT message and code
 typedef struct queue_result{
 	char message[1024];
 	int code;
 } RESULT;
 
 typedef struct queue_result{
 	ELEMENT element;
 	RESULT result;
 } ELEMENT_RESULT;
 
 typedef struct queue_result{
 	int size;
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
<<<<<<< HEAD
  *		been previously deleted. ticket != NULL.
=======
  *		been previously deleted. token != NULL.
>>>>>>> 0b6ac1829effff96c624860c86ddbfe3a7e0178f
  * POSTCONDITION: 
  *		If the ticket is valid and reperesents an existing
  *		queue, it will be deleted. If the ticket is invalid,
  *		the queue is already deleted, or the queue was
  *		already deleted an RESULT will be given. 
  * 
  * 	The RESULT will contain a message and an RESULT code.
  *
  * RESULT CODES:
  *		QUEUE_CANNOT_BE_DELETED
<<<<<<< HEAD
  *		QUEUE_PREVIOUSLY_DELETED
  *		TICKET_INVALID
=======
  *		QUEUE_DOES_NOT_EXIST
  *		TOKEN_INVALID
>>>>>>> 0b6ac1829effff96c624860c86ddbfe3a7e0178f
  ******************************************************/
 RESULT delete_queue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Will place the gien item into the queue represented
  * by the given ticket.
  * 
  * PRECONDITION:
  * 	item != NULL && item.item != NULL &&
  * 	item.priority != NULL && item.priority > 0
  * 	item.priority < 10. item.priority is given as
  * 	0 is least urgent, and 10 is most urgent.
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
  * 	An RESULT will be returned that will contain a 
  * 	RESULT message and RESULT code.
  * 
  * RESULT CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_IS_FULL
  * 	TICKET_INVLAID
  * 	ITEM_INVALID
  ******************************************************/
 RESULT enqueue(ELEMENT item, QUEUE_TICKET token);
 
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
  * 	Will create an RESULT which can be retrieved
  * 	with get_last_RESULT(token). This RESULT will
  * 	contain a message and an RESULT code.
  * 
  * RESULT CODES:
  * 	QUEUE_IS_EMPTY
  * 	QUEUE_DOES_NOT_EXIST
<<<<<<< HEAD
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID
  ******************************************************/
 ELEMENT dequeue(QUEUE_TICKET ticket);
 
 /******************************************************
  * Get the RESULT if any of the last action if any.
  * 
  * Will return the last RESULT for the queue represented
  * by the token.
  *
  * PRECONDITION:
  * 	ticket > 0 and be a valid ticket for a created
  * 	queue, has not been previously deleted, and 
  * 	is_empty() == FALSE.
  * 
  * POSTCONDITION:
  * 	Will return an RESULT that will contain the
  * 	message and RESULT code of the last operation
  * 	on the queue represtned by the given token.
  * 	If no error occured then the RESULT code will
  * 	be SUCCESS and the message will be empty.
  ******************************************************/
 RESULT get_last_result(QUEUE_TICKET token);

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
  * RESULT CODES:
  * 	QUEUE_DOES_NOT_EXIST
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID
=======
  * 	TOKEN_INVLAID
>>>>>>> 0b6ac1829effff96c624860c86ddbfe3a7e0178f
  ******************************************************/
 ELEMENT_RESULT dequeue(QUEUE_TICKET token);
 
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
 boolean is_full(QUEUE_TICKET ticket);
 
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
  * RESULT CODES:
  * 	QUEUE_DOES_NOT_EXIST
<<<<<<< HEAD
  * 	QUEUE_PREVIOUSLY_DELETED
  * 	TICKET_INVLAID 
  ******************************************************/
 ERROR get_last_error(QUEUE_TICKET ticket);
=======
  * 	TOKEN_INVLAID 
  * 	QUEUE_IS_FULL
  * 	QUEUE_IS_NOT_FULL
  ******************************************************/
 RESULT is_full(QUEUE_TICKET ticket);
 
 //need to think about how the size will be returned
 SIZE_RESULT size(QUEUE_TICKET ticket);
>>>>>>> 0b6ac1829effff96c624860c86ddbfe3a7e0178f
 
#endif //STORMO_WARD_PRIORITY_QUEUE
