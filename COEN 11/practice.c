#include <stdio.h>
#include <stdlib.h>
#define NODE struct stuff

struct stuff{


	int num;
	NODE *next;


};

typedef struct list{

	NODE *head;
	NODE *tail;


}LIST;


LIST things[3];

int main(void){



	things[1].head = NULL;

	NODE *p, *k, *f;

	p = (NODE *)malloc(sizeof(NODE));

	p->num = 1000;

	p->next = things[1].head;

	things[1].head = p;

	k = (NODE *)malloc(sizeof(NODE));

	k->num = 100;

	k->next = things[1].head;

	things[1].head = k;

	f = (NODE *)malloc(sizeof(NODE));

	f->num = 10;

	f->next = things[1].head->next;

	things[1].head->next = f;

	NODE *u;
	u = things[1].head;

	while(u != NULL){

		printf("%d \n", u->num);
		u = u->next;

	}


}


