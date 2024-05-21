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

typedef struct list{

	NODE *head;
	NODE *tail;

}LIST;


//Linked List array
LIST array[3];

//Declare counter
int counter = 0;

//Insert function
void insert(char userFirst[], char userLast[], int userAge){
	
	//Loop through array to determine if name is already in array
	if(1 == checkRepeats(userFirst, userLast)){

		//Print error statement and exit function
		printf("\nError: Name already in database\n");
		return;
	
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
		
		//Determine list to populate
		int key;
		if(userAge <= 18)  key = 0;
		else if(userAge < 65) key = 1;
		else key = 2;

		//If list is empty
		if(array[key].head == NULL){
			p->next = NULL;
			array[key].head = p;
			array[key].tail = p;
		}
		//If list has a node
		else if(array[key].head == array[key].tail){
			p->next = NULL;
			array[key].head->next = p;
			array[key].tail = p;
		}
		//If list has 2+ nodes
		else{

			p->next = NULL;
			array[key].tail->next = p;
			array[key].tail = p;

		}
	
	}		
	
}
//View list method
char viewList(void){

	//Declare node pointer
	NODE *p;	

	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\t- 18 and Under\n");

	//Loop through list and print data
	p = array[0].head;

	while(p != NULL){

		printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
		p = p->next;

	}
	
	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\t- 19 to 64\n");

	//Loop through list and print data
	p = array[1].head;

	while(p != NULL){

		printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
		p = p->next;

	}

	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\t- 65 and Over\n");

	//Loop through list and print data
	p = array[2].head;

	while(p != NULL){

		printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
		p = p->next;

	}
	
}

//Cheack for repeats function
int checkRepeats(char firstName[], char lastName[]){

	//Declare node pointer
	NODE *p;

	//Loop through list and compare each name to name passed into function
	int t;
	for(t = 0; t < 3; t++){

		p = array[t].head;
		while(p != NULL){

			//If repeat found, return 1
			if(strcmp(p->firstName, firstName) == 0 && strcmp(p->lastName, lastName) == 0) return 1;
			p = p->next;

		}
	}

	//if no repeat found, return 0
	return 0;

}

//Search for age function
int searchAge(int search){

	//Declare node pointer	
	NODE *p;	

	//Print header
	printf("\n\nFirst\t\tLast\t\tAge\n");

	//Loop through list and check for match in age
	int t;
	for(t = 0; t < 3; t++){

		p = array[t].head;
		while(p != NULL){
	
			if(p->age == search){

				//Print data		
				printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
		

			}

		p = p->next;	

		}
	}

}

//Remove profile function
void removeProfile(char userFirst[], char userLast[]){

	//Declare node pointers
	NODE *p, *q;

	//Loop through list

	int found = 0;
	int t;
	for(t = 0; t < 3; t++){

		
		p = array[t].head;
		while(p != NULL){	

			//If name matches
			if(strcmp(p->firstName, userFirst) == 0 && strcmp(p->lastName, userLast) == 0){ 
				found = 1;
				break;
			}

			q = p;
			p = p->next;


		}


		if(found == 1){
			break;
		}

	}


	//List is empty
	if(p == NULL) return;
	
	//Only one node
	else if(array[t].head == array[t].tail){

		array[t].head->next = NULL;
		array[t].head = array[t].tail = NULL;
		free(p);
		return;

	}
	
	//Deleting head
	else if(array[t].head == p){

		array[t].head = array[t].head->next;
		free(p);
		return;

	}

	//Deleting middle
	else if(p != array[t].tail){

		q->next = p->next;
		free(p);
		return;

	}
	
	//Deleting tail
	else{

		q->next = NULL;
		array[t].tail = q;
		free(p);
	
	}




	//Exit function
		
	return;

			
}

//Save all function
void saveAll(char fileName[]){

	FILE *outfp;
	
	//Open file
	if((outfp = fopen(fileName, "wb")) == NULL){
		printf("Cannot open file\n");
		return;
	}

	//Loop though linked list array
	int k;
	for(k = 0; k < 3; k++){

		NODE *p;
		p = array[k].head;

		while(p != NULL){

			//Write each entry to text file and free each node
			fwrite(p, sizeof(NODE), 1, outfp);
			p = p->next;
		
		}

		if(array[k].head != NULL) deleteAll(array[k].head);

	}
	
	//Close the file
	fclose(outfp);

}

//Read function
void readAll(char fileName[]){

	FILE *infp;
	NODE temp;

	//Open the file
	if((infp = fopen(fileName, "rb")) == NULL){
		printf("Cannot open file\n");
		return;
	}


	//Read each entry in text file and insert to linked lists
	while(fread(&temp, sizeof(NODE), 1, infp) > 0){
	
		insert(temp.firstName, temp.lastName, temp.age);
	}

	fclose(infp);

}

int deleteAll(NODE *current){

	if(current == NULL) return 0;

	deleteAll(current->next); 
	
	free(current);

	return 0;


}

void changeAge(char userFirst[], char userLast[], int oldAge, int newAge){

	

	NODE *p;

	//Loop through list
	int key;

	if(oldAge <= 18) key = 0;
	else if(oldAge < 65) key = 1;
	else key = 2;		

	p = array[key].head;
		while(p != NULL){	

			//If name matches, remove old profile and insert new
			if(strcmp(p->firstName, userFirst) == 0 && strcmp(p->lastName, userLast) == 0){ 
				
				removeProfile(userFirst, userLast);
				insert(userFirst, userLast, newAge);

				return;
			}
			
			p = p->next;
		}

	printf("\nCould not find %s\n", userFirst);
}


//Main function
int main(int argc, char *argu[]){

	if(argc != 2) return;

	//Initialize the linked lists, setting head and tail to NULL
	int z;
	for(z = 0; z < 3; z++){

		array[z].head = NULL;
		array[z].tail = NULL;

	}

	readAll(argu[1]);
	

	int userInput = -1;

	//While loop to run until user chooses exit
	while(userInput != 0){
		
		//Print selection menu
		printf("\nSelect an option:\n1.) Insert new Person\n2.) View List\n3.) Search List for Age\n4.) Remove Profile\n5.) Change Age\n0.) Quit\nSelection: ");
	
		scanf("%d", &userInput);
		int search, newAge, userAge;
		char userFirst[20], userLast[20];

		switch(userInput){
	
		//Quit
		case 0:
			saveAll(argu[1]);		
			 return 0;

		//Run insert function
		case 1:
	
			printf("Enter First Name: ");
			scanf("%s", &userFirst);

			printf("Enter Last Name: ");
			scanf("%s", &userLast);
		
			printf("Enter Age: ");
			scanf("%d", &userAge);
			
			insert(userFirst, userLast, userAge);
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
		
			removeProfile(userFirst, userLast);
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

			changeAge(userFirst, userLast, userAge, newAge);
			break;

		//Print error message
		default:
			
			 printf("\n Selection not recongized, please try again\n");

		
		}	
	}


}


