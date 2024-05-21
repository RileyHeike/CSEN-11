#define NODE struct node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define LIST struct list


extern struct node {

	char firstName[20];
	char lastName[20];
	int age;
	NODE *prev;
	NODE *next;

};

extern struct list{

	NODE *head;
	NODE *tail;

};

extern pthread_mutex_t mutex;

extern LIST array[3];

extern int counter;

void *saving(void *fn);

void insert(char userFirst[], char userLast[], int userAge);

char viewList(void);

int checkRepeats(char firstName[], char lastName[]);

int searchAge(int search);

void removeProfile(char userFirst[], char userLast[]);

void saveAll(char fileName[], int key);

void readAll(char fileName[], int key);

int deleteAll(NODE *current);

void changeAge(char userFirst[], char userLast[], int oldAge, int newAge);

void printBinary(char fn[]);

void printBackwards(int sel);

int printRecursive(NODE *p);
