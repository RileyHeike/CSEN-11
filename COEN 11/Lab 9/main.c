#include "lab9.h"
#define NODE struct node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define LIST struct list

struct node;

struct list;

pthread_mutex_t mutex;

LIST array[3];

int counter;

//Main function
int main(int argc, char *argu[]){

	if(argc != 4) return;

	counter = 0;

	//Initialize the linked lists, setting head and tail to NULL
	int z;
	for(z = 0; z < 3; z++){

		array[z].head = NULL;
		array[z].tail = NULL;

	}

	int key = atoi(argu[3]);

	readAll(argu[1], key);

	pthread_mutex_init(&mutex, NULL);
	
	pthread_t autosave;
	pthread_create(&autosave, NULL, saving, (void *)argu[2]);

	int userInput = -1;

	//While loop to run until user chooses exit
	while(userInput != 0){
		
		//Print selection menu
		printf("\nSelect an option:\n1.) Insert new Person\n2.) View List\n3.) Search List for Age\n4.) Remove Profile\n5.) Change Age\n6.) View Autosave File\n7.) Print List Backwards\n0.) Quit\nSelection: ");
	
		scanf("%d", &userInput);
		int search, newAge, userAge;
		char userFirst[20], userLast[20];

		switch(userInput){
	
		//Quit
		case 0:
			pthread_mutex_lock(&mutex);
			pthread_cancel(autosave);
			pthread_mutex_unlock(&mutex);
			saveAll(argu[1], key);		
			 return 0;

		//Run insert function
		case 1:
	
			printf("Enter First Name: ");
			scanf("%s", &userFirst);

			printf("Enter Last Name: ");
			scanf("%s", &userLast);
		
			printf("Enter Age: ");
			scanf("%d", &userAge);

			pthread_mutex_lock(&mutex);
			insert(userFirst, userLast, userAge);
			pthread_mutex_unlock(&mutex);

			break;
		
		//Run view function
		case 2:			
			viewList();
			break;

		//Scan for search age and pass into search age function
		case 3:
			printf("Enter age to search for: ");
			scanf("%d", &search);
			searchAge(search);
			break;

		//Run remove method
		case 4:
			printf("Enter First Name: ");
			scanf("%s", &userFirst);

			printf("Enter Last Name: ");
			scanf("%s", &userLast);
		
			pthread_mutex_lock(&mutex);
			removeProfile(userFirst, userLast);
			pthread_mutex_unlock(&mutex);			

			break;
		
		//Change age
		case 5:
	
			printf("Enter First Name: ");
			scanf("%s", &userFirst);

			printf("Enter Last Name: ");
			scanf("%s", &userLast);


			printf("Enter Previous Age: ");
			scanf("%d", &userAge);

			printf("Enter New Age: ");
			scanf("%d", &newAge);
			
			pthread_mutex_lock(&mutex);
			changeAge(userFirst, userLast, userAge, newAge);
			pthread_mutex_unlock(&mutex);

			break;
		//Print autosave list
		case 6:
			printBinary(argu[2]);
			break;

		//Print list backwards
		case 7:

			printf("\n1. Print using prev Pointers\n2. Print using Recursion\nSelection: ");
			scanf("%d", &userInput);
			printBackwards(userInput);
			break;

		//Print error message
		default:
			
			 printf("\n Selection not recongized, please try again\n");

		
		}	
	}


}


