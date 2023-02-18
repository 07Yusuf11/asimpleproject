#include <stdio.h>

typedef struct student {
	int    ID;
	char   name[30];
	float  GPA;
	struct student *next;
} Node; 

Node *head = NULL;
Node *cur  = NULL;

void del(Node **head);
void readNode(Node * curr);
void list(Node * list);
void clean(Node * list);
void add(Node ** list, Node ** end);
int  getch();
void studsys(); 
void menu();
