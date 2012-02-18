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
 
 typedef int QUEUE_TICKET;
 typedef int QUEUE_ERROR;
 typedef int PRIORITY;
 
 typedef struct queue_element_struct {
 	int item;
 	PRIORITY priority;
 } ELEMENT;
 
 //need to make some kind of error messages to be checked for
 //
 
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
  ******************************************************/
 int delete_queue(QUEUE_TICKET token);
 
 /******************************************************
  * 
  *
  *
  *
  ******************************************************/
 ELEMENT enqueue(int item, PRIORITY priority, QUEUE_TICKET token);
 
 /******************************************************
  * 
  ******************************************************/
 int dequeue(int item, QUEUE_TICKET token);
 
 /******************************************************
  * Get the error of the last action if any.
  ******************************************************/
 int GET_ERROR(QUEUE_TICKET token);
 
 
#endif //STORMO_WARD_PRIORITY_QUEUE
