/*
 * File: app.c
 */
 #include <unistd.h>
 #include <stdio.h>
 
 
 const char * banner[] = {"\t***********************************************************", 		//1
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
								  
								   
								   
 void display_banner();
 void display_menu();
 void enter_task(char * task, int priority);
 char * get_task();
 int get_number_of_tasks();
 
 void display_banner(){	
	int i;
	for (i = 0; i < 22; i++){
		printf("%s\n",banner[i]);
		system("sleep 1");
   }
 }
 
 int main(){
	 display_banner();
	 return 0;
 }
 
 
