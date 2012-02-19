/*
 * File: priority_queue.h
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This header provides the prototypes for a priority queue library.
 */
 
 #ifndef STORMO_WARD_PRIORITY_QUEUE
 #define STORMO_WARD_PRIORITY_QUEUE
 
 //used a struct to prevent changeing of
 //of primitive typedef changes
 //typedef struct ticket_struct QUEUE_TICKET;
 //struct TB;
 
 //STRUCTS
 typedef int QUEUE_TICKET;
 typedef int PRIORITY;
 
 //USED TO STORE QUEUE ELEMENTS
 typedef struct queue_element_struct {
 	int item;
 	PRIORITY priority;
 } ELEMENT;
 
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
  * If a new priority queue cannot be created then a
  * error will be returned.
  ******************************************************/
 QUEUE_TICKET create_queue();
 
 /******************************************************
  * Deletes a queue
  * 
  * Will attempt to delete the queue represented by the
  * given token.
  * 
  * If queue deletion was unsuccessful then an ERROR
  * will be created. 
  * 
  * You must follow this command with a
  ******************************************************/
 void delete_queue(QUEUE_TICKET token);
 
 /******************************************************
  * 
  *
  *
  *
  ******************************************************/
 void enqueue(ELEMENT item, QUEUE_TICKET token);
 
 /******************************************************
  * 
  ******************************************************/
 ELEMENT dequeue(QUEUE_TICKET token);
 
 /******************************************************
  * Get the error of the last action if any.
  ******************************************************/
 ERROR GET_ERROR(QUEUE_TICKET token);
 
 
#endif //STORMO_WARD_PRIORITY_QUEUE
