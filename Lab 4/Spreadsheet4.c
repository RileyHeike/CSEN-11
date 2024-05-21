#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declare global union, struct,  and struct array

union ageInfo {

	char school[40];
	float salary;
	int yearsRetired;

};

struct profile {
	char firstName[20];
	char lastName[20];
	int age;
	union ageInfo extraInfo;
};


struct profile listProfiles[10];

//Declare counter
int counter = 0;

//Insert function
char insert(void){

	//Declare struct array pointer
	struct profile *p;
	p = listProfiles;

	//Declare local variables for user entry
	char userFirst[20];
	char userLast[20];
	int userAge;
	char school[40];
	float salary;
	int yearsRetired;	


	//Prompt user to enter data and set variables to entered values
	printf("\nEnter First Name: ");
	scanf("%s", &userFirst);

	printf("Enter Last Name: ");
	scanf("%s", &userLast);

	printf("Enter Age: ");
	scanf("%i", &userAge);	
	
	//Collect union info based on input age

	if(userAge <= 18){

		printf("Enter School Name: ");
		scanf("%s", &school);

	}	
	else if(userAge < 65){

		printf("Enter Yearly Salary: ");
		scanf("%f", &salary);

	}
	else{

		printf("Enter Years Since Retirement: ");
		scanf("%d", &yearsRetired);

	}

	//Loop through array to determine if name is already in array
		
	if(1 == checkRepeats(userFirst, userLast)){

		//Print error statement and exit function
		printf("\nError: Name already in database\n");
		return 0;
	
	}

	//Confirm array is not full
	if(counter == 10) printf("\nError: List Full\n");
	else{
				
		//Loop through array
		int i;
		for(i = 0; i <= counter; i++,p++){

			//Check alphabetical order against names in database
			int comp = strcmp(userLast, p->lastName);
			if(comp == 0) comp = strcmp(userFirst, p->firstName);

			//If alphabetically above name being checked
			if(comp < 0 || i == counter){
 
				//Set pointer to counter in array
				p = listProfiles + counter;
	
				//Loop through array from highest slot with data, move every element up 1 slot to make room for new entry
				int k;
				for(k = counter; k > i; k--,p--){
			        
					strcpy(p->firstName,  (p-1)->firstName);
					strcpy(p->lastName, (p-1)->lastName);
					p->age = (p-1)->age;
					if(userAge <= 18) strcpy(p->extraInfo.school, (p-1)->extraInfo.school);
					else if(userAge < 65) p->extraInfo.salary = (p-1)->extraInfo.salary;
					else p->extraInfo.yearsRetired = (p-1)->extraInfo.yearsRetired;
			
			}

			//Add new entry to slot that is now empty
			strcpy(p->firstName, userFirst);	
        	       	strcpy(p->lastName, userLast);
			p->age = userAge;

			if(userAge <= 18) strcpy(p->extraInfo.school, school);
                        else if(userAge < 65) p->extraInfo.salary = salary;
                       	else p->extraInfo.yearsRetired = yearsRetired;
	
			counter++; 
			break;		
	
			}
		
		}	
	
	}		
	
}
//View list method
char viewList(void){

	//Declare array pointer
	struct profile *p;	
	 p = listProfiles;

	//Print header to organize displayed data
	printf("\nFirst\t\tLast\t\tAge\t\tSchool\t\tSalary\t\tYears Retired\n");

	//Loop through array and print data
	int j;
	for(j = 0; j < counter; j++, p++){

		printf("%s\t\t%s\t\t%d\t\t", p->firstName, p->lastName, p->age);
		if(p->age <= 18) printf("%s\n", p->extraInfo.school);
		else if(p->age < 65) printf("\t\t%.0f\n", p->extraInfo.salary);
		else printf("\t\t\t\t%i\n", p->extraInfo.yearsRetired);


	}

}


int checkRepeats(char firstName[], char lastName[]){

	//Declare array pointer
	struct profile *p;
	p = listProfiles;

	//Loop through array and compare each name to name passed into function
	int i;
	for(i = 0; i < counter; i++,p++){

		//If repeat found, return 1
		if(strcmp(p->firstName, firstName) == 0 && strcmp(p->lastName, lastName) == 0) return 1;

	}

	//if no repeat found, return 0
	return 0;

}

//Search for age function
int searchAge(int search){

	//Declare array pointer	
	struct profile *p;	
	p = listProfiles;

	//Loop through array, and print any matches for age entered by user
	int i;

	//Print header

	printf("\nFirst\t\tLast\t\tAge\t\tSchool\t\tSalary\t\tYears Retired\n");

	//Loop through array and check for match in age
	for(i = 0; i < counter; i++, p++){
	
		if(p->age == search){

			//Print data		
			printf("%s\t\t%s\t\t%d\t\t", p->firstName, p->lastName, p->age);
			if(p->age <= 18) printf("%s\n", p->extraInfo.school);
			else if(p->age < 65) printf("\t\t%.0f\n", (p->extraInfo.salary));
			else printf("\t\t\t\t%i\n", p->extraInfo.yearsRetired);

		}	

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

	//Declare array pointer
	struct profile *p;
	p = listProfiles;

	//Loop through array
	int i;
	for(i = 0; i < counter; i++,p++){	

		//If name matches
		if(strcmp(p->firstName, userFirst) == 0 && strcmp(p->lastName, userLast) == 0){

			//Loop through array and move every entry that comes after name to slot-1
			for(i ; i < counter; i++, p++){
				strcpy(p->firstName,  (p+1)->firstName);
				strcpy(p->lastName, (p+1)->lastName);
				p->age = (p+1)->age;
			}

			counter--;		

		}

	}

			
}



void removeProfileAge(int userAge){


	//Declare array pointer
	struct profile *p;
	p = listProfiles;

	//Loop through array
	int i;
	int removals = 0;
	for(i = 0; i < counter; i++,p++){	

		//If name matches
		if(p->age == userAge){

			int k;
			//Loop through array and move every entry that comes after name to slot-1
			for(k = i; k < counter; k++, p++){
				strcpy(p->firstName,  (p+1)->firstName);
				strcpy(p->lastName, (p+1)->lastName);
				p->age = (p+1)->age;

				if(userAge <= 18) strcpy(p->extraInfo.school, (p+1)->extraInfo.school);
				else if(userAge < 65) p->extraInfo.salary = (p+1)->extraInfo.salary;
				else p->extraInfo.yearsRetired = (p+1)->extraInfo.yearsRetired;

			}
			
			removals++;
			removeProfileAge(userAge);	

		}

	}

	//Decrease Counter
	counter -= removals;
			
}

//Main function
int main(void){

	int userInput = -1;

	//While loop to run until user chooses exit
	while(userInput != 0){
		
		//Print selection menu
		printf("\nSelect an option:\n1.) Insert new Person\n2.) View List\n3.) Search List for Age\n4.) Remove Profile\n5.) Remove Profile by Age \n0.) Quit\nSelection: ");
	
		scanf("%d", &userInput);
		int search;
		int userAge;

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
		//Remove Profile by age
		case 5:

			//Prompt user to enter data and scan data into local variables
			printf("\nEnter Age to Remove: ");
			scanf("%d", &userAge);
			removeProfileAge(userAge);
			break;

		//Print error message
		default:
			
			 printf("\n Selection not recongized, please try again\n");

		
		}	
	}


}


