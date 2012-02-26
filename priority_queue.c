 #include "priority_queue.h"
 #include "stdio.h"

 #define MAXIMUM_NUMBER_OF_QUEUES 				1024
 #define MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE	1024

 #define INDEX_OFFSET 0x1221	//Value for obfuscating index in queue_ticket
 #define START_NONCE 0x0502		//Start value for nonce used in queue_ticket

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
	
	if(queue_guard.size >= MAXIMUM_NUMBER_OF_QUEUES)
		outcome.result = set_result(QUEUE_CANNOT_BE_CREATED, "Exceeded maximum number of queues");
	
	if(outcome.result.code == SUCCESS)		//Using outcome's error flag to avoid nested if-else
	{//Create a ticket
		ticket = create_ticket(queue_guard.size);
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

		queue_guard.queues[queue_guard.size] = pQueue;
		queue_guard.size++;		
	}
	output.ticket = ticket;
	return output;
}

RESULT delete_queue(QUEUE_TICKET ticket)
{//Frees a queue struct and it's associated memory
	PRIORITY_QUEUE* pQueue = redeem_ticket(ticket);
	RESULT outcome = set_result(SUCCESS,"");
	if(pQueue != NULL)
	{//Found the queue, delete it
		queue_guard.queues[decrypt_ticket(ticket)] = NULL;	//TODO:refactor?
		queue_guard.size--;
		NODE* pNext;
		NODE* pCur = pQueue->tail;
		while (pCur != NULL)
		{//Traverse linked list freeing nodes
			pNext = pCur->pNext;
			free(pCur);
			pCur = pNext;
		}
		free(pQueue);
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

RESULT enqueue(ELEMENT item, QUEUE_TICKET token)
{
	PRIORITY_QUEUE* pQueue = redeem_ticket(ticket);
	NODE* pNode
	RESULT outcome = set_result(SUCCESS,"");
	if(pQueue == NULL)
		outcome = set_result(TICKET_INVALID,"Provided an invalid queue ticket");
	else if(pQueue->size >= MAXIMUM_NUMBER_OF_ELEMENTS_IN_A_QUEUE)
		outcome = set_result(QUEUE_IS_FULL,"Cannot add to full queue");
	else
	{
		pNode = (NODE*)malloc(sizeof(NODE));
		if(pNode == NULL)
			outcome = set_result(OUT_OF_MEMORY, "Failed to allocate memory");
	}
		
	if(outcome.code == SUCCESS)
	{
	
	}
		
		queue_guard.queues[decrypt_ticket(ticket)] = NULL;	//TODO:refactor?
		queue_guard.size--;
		NODE* pNext;
		NODE* pCur = pQueue->tail;
		while (pCur != NULL)
		{//Traverse linked list freeing nodes
			pNext = pCur->pNext;
			free(pCur);
			pCur = pNext;
		}
		free(pQueue);
	}
	else
	return outcome;
}

ELEMENT_RESULT dequeue(QUEUE_TICKET token);