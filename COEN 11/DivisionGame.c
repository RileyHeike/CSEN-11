#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){

	//Declare correctAnswers and srand
	int correctAnswers = 0;
	srand((int) time(NULL));

	//Delcare for loop variable
	int i;


	//for loop runs 10 times
	for(i = 0; i < 10; i++){

		//Generate divisor, quotient, and calculate dividend	
		int divisor = rand() % 12+1;
		int quotient = rand() % 13; 
		int dividend = divisor*quotient;


		//Print question
		printf("Divide %d by %d \n Answer:  ", dividend, divisor);
		
		//Initialize answer variable and retireve user input 
		int answer;
		scanf("%d", &answer);
	

		//Compare answer to quotient, if correct add 1 to correctAnswers	
		if(answer == quotient){
			correctAnswers++;
			printf("Correct! \n\n");
		}

		//If incorrect print correct asnwer
		else{
			printf("The correct answer is %d\n\n", quotient);
		}

	}


	//Print number of correct answers
	printf("You got %d correct out of 10\n\n", correctAnswers);

	//Exit program
	return 0;
}
