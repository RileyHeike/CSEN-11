#include "lab9.h"
#define NODE struct node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


//Save all function
void saveAll(char fileName[], int key){

	FILE *outfp;
	
	//Open file
	if((outfp = fopen(fileName, "w")) == NULL){
		printf("Cannot open file\n");
		return;
	}

	char line[100];

	//Loop though linked list array
	int k;
	for(k = 0; k < 3; k++){

		NODE *p;
		p = array[k].head;

		while(p != NULL){

			sprintf(line, "%s %s %d\n", p->firstName, p->lastName, p->age);
			
			char *q = line;

			while(*q != '\n'){
				*q ^= key;
				q++;
			}
			//Write each entry to text file and free each node
			fprintf(outfp, "%s", line);
			p = p->next;
		
		}

		deleteAll(array[k].head);

	}
	
	//Close the file
	fclose(outfp);

}

//Read function
void readAll(char fileName[], int key){

	FILE *infp;
	char line[100];
	char *q;	

	//Open the file
	if((infp = fopen(fileName, "r")) == NULL){
		printf("Cannot open file\n");
		return;
	}

	//Declare local variables
	char readFirst[20], readLast[20];
	int readAge;

	//Read each entry in text file and insert to linked lists
	while(fgets(line, 100, infp) != NULL){
		q = line;
		while(*q != '\n'){
			*q ^= key;	
			q++;
		}
		sscanf(line, "%s %s %d", &readFirst, &readLast, &readAge);
		insert(readFirst, readLast, readAge);
	}

	fclose(infp);

}

//Delete all nodes recursively
int deleteAll(NODE *current){

	if(current == NULL) return 0;

	deleteAll(current->next); 
	
	free(current);

	return 0;


}

void *saving(void *fn){
	
	FILE *fp;
	int k;

	while(1){
	//Open the file
	if((fp = fopen("Autosave.txt", "wb")) == NULL){
		printf("Cannot open file\n");
		return;
	}

	//Lock
	for(k = 0; k < 3; k++){
	
		NODE *p;
		p = array[k].head;

		while(p != NULL){
			fwrite(p, sizeof(NODE), 1, fp);
			p = p->next;
		}

	}
	
	//Unlock
	fclose(fp);
	}
	sleep(15);
}

//Print list from autosave file
void printBinary(char fn[]){

	FILE *fp;

	//Open the file
	if((fp = fopen(fn, "rb")) == NULL){
		printf("Cannot open file\n");
		return;
	}

	printf("First\t\tLast\t\tAge\n\n");
	
	int k;
	for(k = 0; k < 3; k++){
	
		NODE temp;
		
		while(fread(&temp, sizeof(NODE), 1, fp) == 1){
			printf("%s\t\t%s\t\t%d\n", temp.firstName, temp.lastName, temp.age);
			
		}

	}


}
//Print lsit backwards using prev pointers
void printBackwards(int sel){

	NODE *p;
	int k;

		printf("\nFirst\t\tLast\t\tAge\n");
		
		for(k=2; k>-1; k--){
	
			if(sel == 1){
			
				p = array[k].tail;
				while(p != NULL){
					printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);
					p = p->prev;
				}

			}
			else{
				printRecursive(array[k].head);
			}

	}

}

//Print list backwards using recursion
int printRecursive(NODE *p){

	if(p == NULL) return;

	printRecursive(p->next);

	printf("%s\t\t%s\t\t%d\n", p->firstName, p->lastName, p->age);

}

