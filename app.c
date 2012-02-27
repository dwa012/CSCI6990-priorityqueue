/*
 * File: app.c
 */
 
#include <stdlib.h>
#include <stdio.h>



void enqueueTask();
void dequeueTask();
void printTask(){}
void createTask(){}

void printMenu()
{
	system("clear");
//TODO: menu title here
	printf("\n\t------------------------------\n");
	printf("\n\t 1. Create Task");
	printf("\n\t 2. Get Next Task");
	printf("\n\t 3. EXIT");	
	printf("\n\t------------------------------\n");
	printf("\n  Enter Your Choice: ");
}

void run()
{
	int choice=0;
	while(choice!=3)
	{
		printMenu();
//		scanf("%1[1234]d%*c",&choice);
		switch(choice)
		{
			case 1:
				createTask();
				break;
			case 2:
				printTask();
				break;
			case 3:
				break;
		}
	}
}

int main()
{
	run();
	return 1;
}
