#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declare global arrays

struct profile {
	char firstName[20];
	char lastName[20];
	int age;
};

struct profile listProfiles[10];

//Declare counter
int counter = 0;

//Insert function
char insert(void){


	struct profile *p;
	p = listProfiles;

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
	scanf("%i", &userAge);	

	char userFullName[40]; 
	strcpy(userFullName, userFirst);
	strcat(userFullName, userLast);
	
	//Loop through array to determine if name is already in array
	int i;
	int slot = -1;
	if(counter == 10) printf("\nError: List Full\n");
	else{
		for(i = 0; i < counter; i++,p++){
		
			char tempFull[40];
			strcat(strcpy(tempFull, p->firstName), p->lastName);

			int comp = strcmp(userFullName, tempFull);
	
			if(comp > 0){
				
			}
			else if(comp == 0){
				slot = -2;
				printf("\nError: Name already in database\n");
				break;
			}
			else {
				slot = i;
				break;		
			}
		
		}	

		if(slot == -1){
			slot = counter;
		}
		if(slot != -2){
			int k;

			//struct profile *q; 
			p = listProfiles; 

			for(k = 0; k < counter; k++, p++);
	
			for(k = counter; k > slot; k--,p--){
			        strcpy(p->firstName,  (p-1)->firstName);
				strcpy(p->lastName, (p-1)->lastName);
				p->age = (p-1)->age;
			}

			strcpy(p->firstName, userFirst);	
                	strcpy(p->lastName, userLast);
			p->age = userAge;
			counter++;
	
		}		
	 
	
	}
}
//View list method
char viewList(void){

	struct profile *p;	
	 p = listProfiles;
	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\n");

	//Loop through array and print data
	int j;
	for(j = 0; j < counter; j++, p++){

		printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);

	}

}


int checkRepeats(char firstName, char lastName){

	int i;
	struct profile *p
	p = listProfiles
	for(i = o; i < counter; i++,p++){

		if(strcmp(p->firstName, firstName) == 0 && strcmp(p->lastName, lastName) == 0) return 1;

	}

	return 0;

}

//Search for age function
int searchAge(int search){
	
	struct profile *p;	
	p = listProfiles;

	//Loop through array, and print any matches for age entered by user
	int i;

	//Print header
	printf("\n\nFirst\t\tLast\t\tAge\n");
	for(i = 0; i < counter; i++, p++){
	
		if(p->age == search){

			//Print data		
			printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);

		}	

	}

}

char removeProfile(void){

	char userFirst[20];
	char userLast[20];


	printf("\nEnter First Name: ");
	scanf("%s", &userFirst);

	
	printf("Enter Last Name: ");
	scanf("%s", &userLast); 

	struct profile *p;
	p = listProfiles;

	int i;

	for(i = 0; i < counter; i++,p++){	
                                                                       
		int comp = strcmp(userFirst, p->firstName) + strcmp(userLast, p->lastName);

		if(comp == 0){

			for(i ; i < counter; i++, p++){
				strcpy(listProfiles[i].firstName,  listProfiles[i+1].firstName);
				strcpy(listProfiles[i].lastName, listProfiles[i+1].lastName);
				listProfiles[i].age = listProfiles[i+1].age;
				counter--;
				return 0;
			}

		
		}

	}
		
	printf("\nName not found\n");
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


