/*
 * File: app.c
 */
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
 
 
 char * banner[] = {"\t***********************************************************", 		//1
								  "\t***********************************************************",
								  "\t**            )    (         )    (     (    (           **", 
								  "\t**  *   )  ( /(    )\\ )   ( /(    )\\ )  )\\ ) )\\ )  *   ) **",
								  "\t**` )  /(  )\\())  (()/(   )\\())  (()/( (()/((()/(` )  /( **", 	//5
								  "\t** ( )(_))((_)\\    /(_)) ((_)\\    /(_)) /(_))/(_))( )(_))**",
								  "\t**(_(_())   ((_)  (_))_    ((_)  (_))  (_)) (_)) (_(_()) **",
								  "\t**|_   _|  / _ \\   |   \\  / _ \\  | |   |_ _|/ __||_   _| **",
								  "\t**  | |   | (_) |  | |) || (_) | | |__  | | \\__ \\  | |   **",
								  "\t**  |_|    \\___/   |___/  \\___/  |____||___||___/  |_|   **", 	//10
								  "\t***********************************************************",
								  "\t***********************************************************",
								  "\t**    Created by Jerry Stormo and Daniel Ward (c) 2012   **",
								  "\t***********************************************************",
								  "\t***********************************************************", 		//15
								  "\t**            Create a prioritized to do list!           **",
								  "\t**                                                       **",  
								  "\t**  “One of the secrets of getting more done is to make  **",
								  "\t**    a TO DO List every day, keep it visible, and use   **",
								  "\t**   it as a guide to action as you go through the day.” **",		//20
								  "\t**               - Jean de La Fontaine                   **",
								  "\t***********************************************************",};	//22
								  
				
 WELCOME_PACKET my_queue;// = create_queue();				
								   
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
 
 void get_task(){
	 ELEMENT_RESULT output = dequeue(my_queue.ticket);
	 
	 system("clear");
	 display_mini_banner();
		
	 if(output.result.code == SUCCESS){
		 printf("\tYour next task:\n");
		 printf("\t%s\n",output.element.item);
	 }
	 else if(output.result.code == QUEUE_IS_EMPTY)
		printf("\tYour todo list is empty!!!\n");
	 else
		printf("\tCould not get the next task from the queue\n");
		
	 // system("sleep 2");
	 //scanf("%1s");
	 //getchar();
	 fgetc(stdin);
 }
 
 void enter_task(char * task, int priority){
		ELEMENT element;
		snprintf(element.item , MAX_STRING_LENGTH -1  ,"%s", task);
		element.priority = priority;
		RESULT output = enqueue(element,my_queue.ticket);
		
		if(output.code == SUCCESS)
			printf("\n\tTask successfully added to the list\n");
		else
			printf("\n\tTask was not added to the list\n");
			
		system("sleep 1");
 }
 
 void create_task(){
		char task[MAX_STRING_LENGTH];
		int priority = 0;
		
	   system("clear");
		display_mini_banner();
	   printf("\n\n\tPlease enter the task information below\n\tPriorities are from 0(lowest) to 10(highest)\n");
	   printf("\t---------------------------------------------------------\n");
		printf("\tEnter name of task: ");
		scanf("%1024s",task);
		printf("\n");
		printf("\tEnter priority of task[0-10]: ");
		scanf("%d",&priority);
		
		enter_task(task,priority);
 }
 
 void display_full_banner(){	
	system("clear");
	
	int i;
	for (i = 0; i < 22; i++){
		printf("%s\n",banner[i]);
		system("sleep .5");
   }
   
   system("sleep 1");
 }
 
 void display_mini_banner(){		
	int i;
	for (i = 0; i < 12; i++){
		printf("%s\n",banner[i]);
   }
 }
 
void printMenu()
{
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
{
	int choice=0;
	while(choice!=3)
	{
		printMenu();
		scanf("%d",&choice);
		perform_choice(choice);	
	}
}

void perform_choice(int choice){
		switch(choice)
		{
			case 1:
				create_task();
				break;
			case 2:
				get_task();
				break;
			case 3:
				printf("\tLATER DUDE!!!!!!!!!!!!\n");
				break;
		}
}

 void start_music(){
	system("timidity ff4-The_Prelude.mid >> /dev/null &");
 }
 
 void stop_music(){
	 system("killall timidity");
 }

int main()
{
	my_queue = create_queue();	
	if(my_queue.result.code == SUCCESS){
		//start_music();
		//display_banner();
		run();
		//stop_music();
		
		delete_queue(my_queue.ticket);
	}
	else
		printf("ERROR: Could not create queue for to-do list.\n");
		
	return 0;
}
 
