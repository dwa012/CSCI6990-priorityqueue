/*
 * File: priority_queue.h
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This header provides the prototypes for a priority queue library.
 */
 
 #ifndef STORMO_WARD_PRIORITY_QUEUE
 #define STORMO_WARD_PRIORITY_QUEUE
 
 enum ERRORS {CREATION_FAILED,DELETION_FAILED};
 
 //maybe use a struct for the tokens for queues
 
 /******************************************************
  * Creates a new priority queue to be used. 
  * 
  * If the queue is created successfully a token will
  * be returned. This token will need to be presented
  * when any queue operations are to be requested.
  *
  * If a new priority queue cannot be created then
  * error will be produced.
  ******************************************************/
 int create_queue();
 
 /******************************************************
  * Deletes a queue
  * 
  * Will attempt to delete the queue represented by the
  * given token.
  * 
  ******************************************************/
 int delete_queue(int token);
 
 /******************************************************
  * 
  ******************************************************/
 int enqueue(int item, int token);
 
 /******************************************************
  * 
  ******************************************************/
 int dequeue(int item, int token);
 
 
#endif STORMO_WARD_PRIORITY_QUEUE
