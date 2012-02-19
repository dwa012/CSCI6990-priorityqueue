#include "priority_queue.h"
#include <stdio.h>

int main(){
	//QUEUE_TICKET qt;
	//printf("test");
	//int i = QUEUE_FULL;
	QUEUE_TICKET tick = create();
	//enqueue(233, 32);
	ERROR e = get_last_error(123);
	printf("Message: %s Code: %d\n",e.message,e.code);
	return 0;
}
