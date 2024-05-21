#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declare global arrays
char firstNames[10][20];
char lastNames[10][20];
int ages[10];

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
	scanf("%i", &userAge);	
	
	//Loop through array to determine if name is already in array
	int isRepeat = 0;
	int i;
	for(i = 0; i < counter; i++){
	
		if(strcmp(userFirst, firstNames[i]) == 0 && strcmp(userLast, lastNames[i]) == 0){
			isRepeat = 1;
			break;

		}	

	}	

	//If name is already in array, print error message
	if(isRepeat == 1) printf("\nError: Repeat name\n");
	
	//If array is full, print error message
	else if(counter == 10) printf("\nError: List Full\n"); 
	
	//Else, add data to arrays and increase counter
	else{
		strcpy(firstNames[counter], userFirst);
		strcpy(lastNames[counter], userLast);
		ages[counter] = userAge;	
		counter++;
	}
	
}

//View list method
char viewList(void){
	
	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\n");

	//Loop through array and print data
	int j;
	for(j = 0; j < counter; j++){

		printf("%s\t\t%s\t\t%d\n", firstNames[j], lastNames[j], ages[j]);

	}

}

//Search for age function
int searchAge(int search){
	
	//Loop through array, and print any matches for age entered by user
	int i;

	//Print header
	printf("\n\nFirst\t\tLast\t\tAge\n");
	for(i = 0; i < counter; i++){
	
		if(ages[i] == search){

			//Print data		
			printf("%s\t\t%s\t\t%d\n", firstNames[i], lastNames[i], ages[i]);

		}	

	}

}

//Main function
int main(void){

	int userInput = -1;

	//While loop to run until user chooses exit
	while(userInput != 0){
		
		//Print selection menu
		printf("\nSelect an option:\n1.) Insert new Person\n2.) View List\n3.) Search List for Age\n0.) Quit\nSelection: ");
	
		scanf("%d", &userInput);
	
		//Quit
		if(userInput == 0) return 0;

		//Run insert function
		else if(userInput == 1){
		
			insert();

		}
		
		//Run view function
		else if(userInput == 2){
			
			viewList();

		}

		//Scan for search age and pass into search age function
		else if(userInput == 3){
			int search;
			printf("Enter age to search for: ");
			scanf("%d", &search);
			searchAge(search);

		}

		//Print error message
		else printf("\n Selection not recongized, please try again\n");

	
		
	}


}


