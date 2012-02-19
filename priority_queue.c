#include "priority_queue.h"
//#include <stdio.h>

 typedef char bool;

 #define MAXIMUM_NUMBER_OF_QUEUES 				1024
 #define MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE	1024

 #define TRUE	1
 #define FALSE	0

 static ERROR last_error;


 QUEUE_TICKET create(){	
	return 0;
 }

 ERROR enqueue(ELEMENT item, QUEUE_TICKET token){
 	//ELEMENT e = item;
	return last_error;
 }
 
 ERROR get_last_error(QUEUE_TICKET token){
	 snprintf(last_error.message,sizeof(last_error.message),"test");
	 last_error.code =1;
	 return last_error;
 }
