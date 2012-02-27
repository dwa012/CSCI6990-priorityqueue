/*
 * File: app.c
 * Authors: Jeremy Stormo & Daniel Ward
 *
 * This program is a simple todo list application that will
 * have the user enter a task and the associated priority.
 * 
 * The task that will be at the top of the list will always
 * be the task that is the oldest with the highest priority.
 * 
 * This application uses some unix system calls, therefore
 * it will need to be altered to run on another system.
 * It also need the timidy application installed and a
 * midi in the same executing folder to run properly.
 */
 
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
 
 
char * banner[] =  {"\t***********************************************************", 	//1
						  "\t***********************************************************",
						  "\t**            )    (         )    (     (    (           **", 
						  "\t**  *   )  ( /(    )\\ )   ( /(    )\\ )  )\\ ) )\\ )  *   ) **",
						  "\t**` )  /(  )\\())  (()/(   )\\())  (()/( (()/((()/(` )  /( **", //5
						  "\t** ( )(_))((_)\\    /(_)) ((_)\\    /(_)) /(_))/(_))( )(_))**",
						  "\t**(_(_())   ((_)  (_))_    ((_)  (_))  (_)) (_)) (_(_()) **",
						  "\t**|_   _|  / _ \\   |   \\  / _ \\  | |   |_ _|/ __||_   _| **",
						  "\t**  | |   | (_) |  | |) || (_) | | |__  | | \\__ \\  | |   **",
						  "\t**  |_|    \\___/   |___/  \\___/  |____||___||___/  |_|   **", //10
						  "\t***********************************************************",
						  "\t***********************************************************",
						  "\t**    Created by Jerry Stormo and Daniel Ward (c) 2012   **",
						  "\t***********************************************************",
						  "\t***********************************************************", 	//15
						  "\t**            Create a prioritized to do list!           **",
						  "\t**                                                       **",  
						  "\t**  “One of the secrets of getting more done is to make  **",
						  "\t**    a TO DO List every day, keep it visible, and use   **",
						  "\t**   it as a guide to action as you go through the day.” **",	//20
						  "\t**               - Jean de La Fontaine                   **",
						  "\t***********************************************************",};	//22
								  
//Welcome packet contains the ticket for our queue
 WELCOME_PACKET my_queue;
								   
 void run();
 
 //// PRINTING TO SCREEN PROTOTYPES
 void print_menu();								   
 void display_full_banner();
 void display_mini_banner();
 void display_menu();
 
 //// TASK PROTOTYPES
 void enter_task(char * task, int priority);
 void get_task();
 int get_number_of_tasks();
 
 //// MUSIC PROTOYPES
 void start_music();
 void stop_music();
 
 //// USER ITERACTIPON PROTOTYPES
 int get_menu_choice();
 void create_task();
 void perform_choice(int choice); 
 
 void get_task(){//Request the next task of most importance from queue
	 ELEMENT_RESULT output = dequeue(my_queue.ticket);
	 
	 system("clear");
	 display_mini_banner();
		
	 if(output.result.code == SUCCESS){//Got task, display it's data
		 printf("\tYour next task:\n");
		 printf("\t%s\n",output.element.item);
	 }
	 else if(output.result.code == QUEUE_IS_EMPTY)//Task list is empty
		printf("\tYour todo list is empty!!!\n");
	 else
		printf("\tCould not get the next task from the queue\n");//Encountered another error code
		
	 system("sleep 2");//let user read task
 }
 
 void enter_task(char * task, int priority){//Add task to the todo list
		ELEMENT element;
		snprintf(element.item , MAX_STRING_LENGTH -1  ,"%s", task);
		element.priority = priority;
		RESULT output = enqueue(element,my_queue.ticket);//Give task to the queue
		
		if(output.code == SUCCESS)//Queue added task successfully
			printf("\n\tTask successfully added to the list\n");
		else
			printf("\n\tTask was not added to the list\n");//Queue threw an error
			
		system("sleep 1");
 }
 
 void create_task(){//Allow user to create a new task
		char task[MAX_STRING_LENGTH];
		int priority = 0;
		
	   system("clear");
		display_mini_banner();
	   printf("\n\n\tPlease enter the task information below\n\tPriorities are from 0(lowest) to 10(highest)\n");
	   printf("\t---------------------------------------------------------\n");
		printf("\tEnter name of task: ");
		scanf("%1024s",task);		//Get description of the task
		printf("\n");
		printf("\tEnter priority of task[0-10]: ");
		scanf("%d",&priority);		//Get the importance of the task
		
		enter_task(task,priority);
 }
 
 void display_full_banner(){//Display the scrolling banner on startup
	system("clear");	
	int i;
	for (i = 0; i < 22; i++){//Iterate through the banner line by line
		printf("%s\n",banner[i]);
		system("sleep .5");
   }   
   system("sleep 1");
 }
 
 void display_mini_banner(){//Display the brief banner above menu uis
	int i;
	for (i = 0; i < 12; i++){
		printf("%s\n",banner[i]);
   }
 }
 
void printMenu()
{//Print the basic option menu for the application
	system("clear");
	display_mini_banner();
	printf("\n\t------------------------------\n");
	printf("\n\t 1. Create Task");
	printf("\n\t 2. Get Next Task");
	printf("\n\t 3. EXIT");	
	printf("\n\t------------------------------\n");
	printf("\n\tEnter Your Choice: ");
}

void run()
{//Run the application until the user quits
	int choice=0;
	while(choice!=3)//Choice 3 is the EXIT choice in printMenu
	{
		printMenu();
		scanf("%d",&choice);
		perform_choice(choice);	//Handoff choice to function to do the actual decision making
	}
}

void perform_choice(int choice){//Decide on how to handle the menu choices
	switch(choice)
	{
		case 1:	//Make a new task
			create_task();
			break;
		case 2:
			get_task();	//Get the next most important task
			break;
		case 3:		//Quit the application
			printf("\tLATER DUDE!!!!!!!!!!!!\n");
			break;
	}
}

 void start_music(){//Little bit of fun music
	system("timidity ff4-The_Prelude.mid >> /dev/null &");
 }
 
 void stop_music(){//Kill all the fun
	 system("killall timidity");
 }

int main()
{
	my_queue = create_queue();	
	if(my_queue.result.code == SUCCESS){//Got a queue from library
		start_music();				//Music
		display_full_banner();	//Lights
		run();						//Camera!
		stop_music();
		
		delete_queue(my_queue.ticket);//Cleanup our queue because we're good people
	}
	else	//Library gave us an error on making queue
		printf("ERROR: Could not create queue for to-do list.\n");
		
	return 0;
}
 
