 #include "priority_queue.h"
 #include "stdio.h"
 
 /************ INTERNAL DEFINES ************/
 #define MAXIMUM_NUMBER_OF_QUEUES 				1024
 #define MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE	1024

 #define INDEX_OFFSET 0x1221	//Value for obfuscating index in queue_ticket
 #define START_NONCE 0x0502		//Start value for nonce used in queue_ticket
 #define TRUE 1
 #define FALSE 0
 
 typedef char boolean;
 /********** END INTERNAL DEFINES **********/

 /************ INTERNAL STRUCTS ************/
 typedef struct node 
 {
 	struct node* pNext;
	struct node* pPrev;
	ELEMENT item;
 } NODE;
 
 typedef struct priority_queue 
 {
	NODE* head;
	NODE* tail;
	uint size;
	QUEUE_TICKET ticket;
 } PRIORITY_QUEUE;

 typedef struct queue_manager 
 {
	PRIORITY_QUEUE* queues[MAXIMUM_NUMBER_OF_QUEUES];
	uint size;
 }QUEUE_MANAGER;
 /************ END INTERNAL STRUCTS ************/
 
 /************ INTERNAL PROTOTYPES ************/
 static int find_open_slot();
 static QUEUE_TICKET create_ticket(uint index);
 static void free_queue(PRIORITY_QUEUE* pQueue);
 static int decrypt_ticket(QUEUE_TICKET ticket);
 static RESULT set_result(int resultCode, char* message);
 static PRIORITY_QUEUE* redeem_ticket(QUEUE_TICKET ticket);
  static ELEMENT remove_one_element(PRIORITY_QUEUE* pQueue);
 static void insert_node(PRIORITY_QUEUE* pQueue, NODE* pNode);
 /********** END INTERNAL PROTOTYPES ************/

static uint nonce = START_NONCE;	//Nonce counter for queue ticket creation
static QUEUE_MANAGER queue_guard;	//Guard for queue, obfuscates the location of the queue

static RESULT set_result(int resultCode, char* message)
{
	RESULT outcome;
	outcome.code = resultCode;
	snprintf(outcome.message,sizeof(outcome.message),"%s",message);
	return outcome;
}

static QUEUE_TICKET create_ticket(uint index)
{//Create queue_ticket given an index
	QUEUE_TICKET ticket = 0;
	uint high = 0;		//Obfuscated index value to put into high 16 bits
	uint low = 0;		//Nonce	value to put into low 16 bits

	while(low == 0){			//Assign nonce such that it's non-trivial, try again if it is
		low = nonce & 0xffff;	//Cut off upper 16 bits of nonce
		nonce = nonce + 1;
	}

	high = (index + INDEX_OFFSET) & 0x7fff;	//Obfuscate index, force positive and cuts to 16 bits
	if(high == index + INDEX_OFFSET)	//Check that real index didn't get trashed by obfuscation
		ticket = (high << 16) | low;	//Create ticket by combining obfuscated index and nonce

	return ticket;	//return valid ticket, NULL if failed
	//Should only ever fail by giving a bad index, 
	//one which will overflow when combined with the INDEX_OFFSET. 
	//So it's dependent on MAXIMUM_NUMBER_OF_QUEUES and INDEX_OFFSET not 
	//adding together to exceed 16 bits
	//If it does, then there will be indices in the array for which tickets cannot be created
}

static int decrypt_ticket(QUEUE_TICKET ticket)
{//Pulls the index value out of a ticket
	int index = ticket >> 16;		//Pull off top 16 bits of ticket
	return (index - INDEX_OFFSET);	//Remove obfuscation
}

static PRIORITY_QUEUE* redeem_ticket(QUEUE_TICKET ticket)
{//Given ticket, returns pointer to queue requested
	int index = decrypt_ticket(ticket);	//Get index from the ticket
	PRIORITY_QUEUE* pQueue = NULL;

	if(index < MAXIMUM_NUMBER_OF_QUEUES	//If index is in valid queue range
		&& index >= 0)
		pQueue = queue_guard.queues[index];	//Get queue at index from manager
	if(pQueue != NULL
		&& pQueue->ticket != ticket)	//If queue wasn't found or ticket didn't match queue's copy
		pQueue = NULL;					//Setup to return NULL

	return pQueue;
}

WELCOME_PACKET create_queue()
{//Create a new queue in the queue manager returning its ticket
//TODO:refactor
	WELCOME_PACKET outcome;
	QUEUE_TICKET ticket = 0;
	outcome.result = set_result(SUCCESS,"");
	PRIORITY_QUEUE* pQueue = NULL;
	int indexFound = find_open_slot();
		
	if(indexFound == -1)
		outcome.result = set_result(QUEUE_CANNOT_BE_CREATED, "Exceeded maximum number of queues");
	
	if(outcome.result.code == SUCCESS)		//Using outcome's error flag to avoid nested if-else
	{//Create a ticket
		ticket = create_ticket(indexFound);
		if(ticket == 0)
			outcome.result = set_result(QUEUE_CANNOT_BE_CREATED, "Ticket creation failed");
	}
	
	if(outcome.result.code == SUCCESS)
	{//Malloc new queue
		pQueue = (PRIORITY_QUEUE*) malloc(sizeof(PRIORITY_QUEUE));
		if(pQueue == NULL)
			outcome.result = set_result(OUT_OF_MEMORY, "Failed to allocate memory");
	}
	
	if(outcome.result.code == SUCCESS)
	{//Initialize new queue
		pQueue->ticket = ticket;
		pQueue->size = 0;
		pQueue->head = NULL;
		pQueue->tail = NULL;

		queue_guard.queues[indexFound] = pQueue;
		queue_guard.size++;		
	}
	outcome.ticket = ticket;
	return outcome;
}

RESULT delete_queue(QUEUE_TICKET ticket)
{//Free a queue struct and it's associated memory
	RESULT outcome = set_result(SUCCESS,"");
	PRIORITY_QUEUE* pQueue = redeem_ticket(ticket);

	//Ticket returned a valid queue, delete it
	if(pQueue != NULL)
	{	
		queue_guard.queues[decrypt_ticket(ticket)] = NULL;	//remove refernce in the array of queues
		queue_guard.size = queue_guard.size - 1;	//decrement the size
		
		free_queue(pQueue);
	}
	else
		outcome = set_result(TICKET_INVALID,"Provided an invalid queue ticket");
		
	return outcome;
}

SIZE_RESULT get_size(QUEUE_TICKET ticket)
{//Returns the current size of the queue requested
	SIZE_RESULT outcome;
	PRIORITY_QUEUE* pQueue = redeem_ticket(ticket);
	
	if(pQueue != NULL)
	{//Found the queue, get size
		outcome.size = pQueue->size;
		outcome.result = set_result(SUCCESS,"");
	}
	else
	{//Invalid ticket
		outcome.size = 0;
		outcome.result = set_result(TICKET_INVALID, "Provided an invalid queue ticket");
	}
	return outcome;	
}

static void insert_node(PRIORITY_QUEUE* pQueue, NODE* pNode)
{//TODO: refactor
//	printf("* insert_node: ln204\n");//DEBUG
	boolean finished = FALSE;
	if(pQueue->tail == NULL)
	{//Insert into empty list
		pQueue->tail = pNode;
		pQueue->head = pNode;
		pNode->pNext = NULL;
		pNode->pPrev = NULL;
		finished = TRUE;
	}
	NODE* curNode = pQueue->tail;
	while(finished == FALSE
		&& curNode != NULL)
	{
		if(curNode->item.priority < pNode->item.priority)
			curNode=curNode->pNext;	//Iterate to next node
		else
		{//Insert new node before curNode

			//Update new node's links
			pNode->pPrev = curNode->pPrev;
			pNode->pNext = curNode;

			if(pNode->pPrev == NULL)	//Adding to tail of queue
				pQueue->tail = pNode;	//Update tail
			else										//Adding inbetween nodes
				pNode->pPrev->pNext = pNode;	//Update prior node's links

			//Update curNode's links
			curNode->pPrev = pNode;

			finished = TRUE;
		}
	}
	if(finished == FALSE)
	{//Hit end of list, add to head of queue
		curNode = pQueue->head;	//Add after the curNode

			//Update new node's links
			pNode->pPrev = curNode;
			pNode->pNext = NULL;

			//Update curNode's links
			curNode->pNext = pNode;

			//Update head link
			pQueue->head = pNode;		
	}

	pQueue->size += 1;
}

RESULT enqueue(ELEMENT item, QUEUE_TICKET ticket)
{
	PRIORITY_QUEUE* pQueue = redeem_ticket(ticket);
	NODE* pNode;
	RESULT outcome = set_result(SUCCESS,"");

//	printf("* enqueue: ln259\n");//DEBUG
	if(pQueue == NULL)
		outcome = set_result(TICKET_INVALID,"Provided an invalid queue ticket");
	else if(item.priority > 10)
	{
		outcome = set_result(ITEM_INVALID,"Priority outside of legal range");
//		printf("*** enqueue FAIL: Item Invalid\n");//DEBUG
	}
	else if(pQueue->size >= MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE)
		outcome = set_result(QUEUE_IS_FULL,"Cannot add to full queue");
	
	else
	{
		pNode = (NODE*)malloc(sizeof(NODE));
		if(pNode == NULL)
			outcome = set_result(OUT_OF_MEMORY, "Failed to allocate memory");
//			printf("* enqueue: ln274\n");//DEBUG
	}

	if(outcome.code == SUCCESS)
	{
		pNode->item = item;
		insert_node(pQueue, pNode);
	}
	return outcome;
}

ELEMENT_RESULT dequeue(QUEUE_TICKET ticket)
{
	ELEMENT_RESULT outcome; //the result of the dequeue
	snprintf(outcome.element.item,MAX_STRING_LENGTH," ");
	outcome.element.priority = 0;// = {"",0};  //DEBUG JERRY
	//outcome.element = {NULL,0};
	outcome.result = set_result(SUCCESS,"");
	
	//get the queue represented by the ticket
	PRIORITY_QUEUE* pQueue = redeem_ticket(ticket);
	
	if(pQueue == NULL) //if NULL the mark it as an error
		outcome.result = set_result(TICKET_INVALID,"Provided an invalid queue ticket");
	else if(pQueue->size == 0) //if the size is 0 then mark an error
		outcome.result = set_result(QUEUE_IS_EMPTY,"Cannot dequeue from an empty queue");
	else
		//if the ticket is valid and the size > 0 then remove one element
		outcome.element = remove_one_element(pQueue);
		
	return outcome;
}

RESULT is_full(QUEUE_TICKET ticket){
	SIZE_RESULT size = get_size(ticket);

	if(size.result.code == SUCCESS)
	{
		if(size.size >= MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE)
			size.result = set_result(QUEUE_IS_FULL,"Queue is full");
		else
			size.result = set_result(QUEUE_IS_NOT_FULL,"Queue is not full");
	}

	return size.result;	
}

static int find_open_slot(){
	int result = -1;
	int index;
	
	for(index = 0; index < MAXIMUM_NUMBER_OF_QUEUES && result == -1; index++)
		if(queue_guard.queues[index] == NULL)
			result = index;
			
	return result;
}

static ELEMENT remove_one_element(PRIORITY_QUEUE* pQueue)
{
	ELEMENT result = pQueue->head->item;
	NODE* temp_node = pQueue->head;

	pQueue->head = pQueue->head->pPrev;
	if(pQueue->head != NULL)
		pQueue->head->pNext = NULL;
	else
		pQueue->tail = NULL;
		
	free(temp_node);	
	
	pQueue->size = pQueue->size - 1;
	return result;
}

static void free_queue(PRIORITY_QUEUE* pQueue){
	NODE* pNext;
	NODE* pCur = pQueue->tail;
	
	//Traverse linked list freeing each node
	while (pCur != NULL)
	{
		//set the next node to traverse to
		pNext = pCur->pNext;
		//free the current node
		free(pCur);
		//swap the current with the next node
		pCur = pNext;
		
	}//end while
	
	//free the queue
	free(pQueue);
}
