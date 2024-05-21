#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODE struct node

//Declare global struct and struct array

struct node {
	char firstName[20];
	char lastName[20];
	int age;
	NODE *next;
};

//Create empty list
NODE *head = NULL;

//Declare counter
int counter = 0;

//Insert function
char insert(void){

	//Declare local variables for user entry
	char userFirst[20];
	char userLast[20];
	int userAge;
	
	//Prompt user to enter data and set variables to entered values
	printf("\nEnter First Name: ");
	scanf("%s", &userFirst);

	printf("Enter Last Name: ");
	scanf("%s", &userLast);

	printf("Enter Age: ");
	scanf("%d", &userAge);	
	
	//Loop through array to determine if name is already in array
	if(1 == checkRepeats(userFirst, userLast)){

		//Print error statement and exit function
		printf("\nError: Name already in database\n");
		return 0;
	
	}

	//Confirm array is not full
	if(counter == 10) printf("\nError: List Full\n");
	else{

		//Create node pointer and memory
		NODE *p;
		p = (NODE *)malloc(sizeof(NODE));

		//Populate with entered info
		strcpy(p->firstName, userFirst);
		strcpy(p->lastName, userLast);
		p->age = userAge;

		//If list is empty
		if(head == NULL){

			p->next = NULL;
			head = p;

		}

		//If list has nodes
		else{
		
			p->next = head;
			head = p;

		}
	
	}		
	
}
//View list method
char viewList(void){

	//Declare node pointer
	NODE *p;	
	p = head;

	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\n");

	//Loop through list and print data
	while(p != NULL){

		printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
		p = p->next;

	}

}

//Cheack for repeats function
int checkRepeats(char firstName[], char lastName[]){

	//Declare node pointer
	NODE *p;
	p = head;

	//Loop through list and compare each name to name passed into function
	while(p != NULL){

		//If repeat found, return 1
		if(strcmp(p->firstName, firstName) == 0 && strcmp(p->lastName, lastName) == 0) return 1;
		p = p->next;

	}
	//if no repeat found, return 0
	return 0;

}

//Search for age function
int searchAge(int search){

	//Declare node pointer	
	NODE *p;	
	p = head;

	//Print header
	printf("\n\nFirst\t\tLast\t\tAge\n");

	//Loop through list and check for match in age
	while(p != NULL){
	
		if(p->age == search){

			//Print data		
			printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
		

		}

	p = p->next;	

	}


}

//Remove profile function
char removeProfile(void){

	//Declare local variables to store user entry
	char userFirst[20];
	char userLast[20];

	//Prompt user to enter data and scan data into local variables
	printf("\nEnter First Name: ");
	scanf("%s", &userFirst);

	
	printf("Enter Last Name: ");
	scanf("%s", &userLast); 

	//Declare node pointers
	NODE *p, *q;
	p = head;
	q = head;

	//Loop through list
	while(p != NULL){	

		//If name matches
		if(strcmp(p->firstName, userFirst) == 0 && strcmp(p->lastName, userLast) == 0) break;
	
		q = p;
		p = p->next;

	}

	//List is empty
	if(p == NULL) return;
	
	//Only one node
	else if(head->next == NULL) {

		head = NULL;
		free(p);
		return;

	}
	
	//Deleting head
	else if(head == p){

		head = head->next;
		free(p);
		return;

	}

	//Deleting middle or end node
	else{

		q->next = p->next;
		free(p);
		return;

	}




	//Exit function
		
	return 0;

			
}
//Main function
int main(void){

	int userInput = -1;

	//While loop to run until user chooses exit
	while(userInput != 0){
		
		//Print selection menu
		printf("\nSelect an option:\n1.) Insert new Person\n2.) View List\n3.) Search List for Age\n4.) Remove Profile\n0.) Quit\nSelection: ");
	
		scanf("%d", &userInput);
		int search;

		switch(userInput){
	
		//Quit
		case 0:
			
			 return 0;

		//Run insert function
		case 1:
			
			insert();
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

			removeProfile();
			break;

		//Print error message
		default:
			
			 printf("\n Selection not recongized, please try again\n");

		
		}	
	}


}


