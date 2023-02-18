#include <stdio.h> 
#include <stdlib.h> 
#include <termio.h>
#include <unistd.h>
#include <string.h>

//参数传递：传值，传值
//传值的形参随着函数返回而消失，传地址可以对其指向的内存作修改

typedef struct student {
	int    ID;
	char   name[30];
	float  GPA;
	struct student *next;
} Node; 

extern Node *head,*cur;

void search(Node *list) {
	if (list != NULL) {
		printf("\t\t\t\t\t|Enter ID: ");
		int ID;
		scanf("%d",&ID);
		while (1) {
			if (ID == list -> ID) {
				printf("\t\t\t\t\t|Found!\n");
				printf("\t\t\t\t\t|-ID-|--------Name---------|-GPA-|\n");
				printf("\t\t\t\t\t|%4d|%21s|%5.1f|\n",list -> ID, list -> name, list -> GPA);
				sleep(2);
				return;
			}
			if (list -> next == NULL) {
				printf("\t\t\t\t\t|Not Found!\n");
				sleep(1);
				return;
			}
			list = list -> next;
		}
	}
	else {
		printf("\t\t\t\t\t|Empty.\n");
		sleep(1);
		return;
	}
}

void del(Node **head) {
	Node *cur = *(head);
	Node *pre;
	if (cur != NULL) {
		printf("\t\t\t\t\t|Enter Name: ");
		char str[30];
		int  a;
		scanf("%s",str);
		while (1) {
			a = strcmp((cur -> name),str);
			if (a == 0) {
				if (cur == *(head)) {
					*(head) = (*(head)) -> next;
					free(cur);
					printf("\t\t\t\t\t|Deleted.\n");
					sleep(1);
					return;
				}
				printf("\t\t\t\t\t|Found %s Delete?(y/n): ", str);
				char c = getchar();
				if (c == 'y') {
					pre -> next = cur -> next;
					free(cur);
					printf("\t\t\t\t\t|Deleted.\n");
					sleep(1);
					return;
				}
			}
			if (cur -> next == NULL) {
				printf("\t\t\t\t\t|Not Found!\n");
				sleep(1);
				return;
			}
			pre = cur;
			cur = cur -> next;
		}
	}
	else {
		printf("\t\t\t\t\t|Empty\n");
		sleep(1);
		return;
	}

}

int getch() {
	int cr;
	struct termios nts, ots;
	if (tcgetattr(0, &ots) < 0)
		return EOF;
	nts = ots;
	cfmakeraw(&nts);
	if (tcsetattr(0, TCSANOW, &nts) < 0)
		return EOF;
	cr = getchar();
	if (tcsetattr(0, TCSANOW, &ots) < 0)
		return EOF;
	return cr;
}

void readNode(Node * curr) {
	char c;
	printf("\t\t\t\t\t|Enter ID: ");
	scanf("%d",&(curr -> ID));
	printf("\t\t\t\t\t|Enter name: ");
	scanf("%c",&c);
	scanf("%[^\n]",curr -> name );
	printf("\t\t\t\t\t|Enter GPA: ");
	scanf("%f",&(curr -> GPA));
	return ;
}

//已解决：最后一个节点不打印。
//未解决：输入名字不能带空格，未清空缓存。
void list(Node * list) {
	if(list != NULL) {
		printf("\e[1;1H\e[2J"); //clean screen
		printf("\t\t\t\t\t|-ID-|--------Name---------|-GPA-|\n");
		while (1) {
			//printf("list = %p\n",list);
			printf("\t\t\t\t\t|%4d|%21s|%5.1f|\n",list -> ID, list -> name, list -> GPA);
			if (list -> next == NULL)
				break;
			list = list -> next;
		}
		printf("\t\t\t\t\t|Press any key to continue: ");
		char c;
		c = getch();
		return;
	}
	else
		printf("\t\t\t\t\t|No records!\n");
		sleep(1);
		return;
}

void clean(Node * head) {
	while (head != NULL) {
		Node *temp = head;
		head = head -> next;
		free(temp);
	}
	return;
}

void add(Node ** list, Node ** end) {
//	printf("head = %p\n",*list);
	//printf("end = %p\n",*end);
	sleep(1);
	if (*list == NULL) {
		*list = (Node *) malloc(sizeof(Node));
		*end  = *list;
		(*end) -> next = NULL;
		readNode(* end);
		//printf("head = %p\n",*list);
		//printf("end = %p\n",*end);
		sleep(1);
	}
	else {
		while ((*end) -> next != NULL) 
			*end = (*end) -> next;
		(*end) -> next = (Node *)malloc(sizeof(Node));
		*end = (*end) -> next;
		(*end) -> next = NULL;
		//printf("head = %p\n",*list);
		//printf("end = %p\n",*end);
		readNode(*end);
	}
}

void menu() {
	printf("\e[1;1H\e[2J"); //clean screen
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t|--------------------------------|\n");
	printf("\t\t\t\t\t|---Students Management System---|\n");
	printf("\t\t\t\t\t|-----Press A Number To Start----|\n");
	printf("\t\t\t\t\t|1.Add A Student                 |\n");
	printf("\t\t\t\t\t|2.Search                        |\n");
	printf("\t\t\t\t\t|3.List All Student              |\n");
	printf("\t\t\t\t\t|4.Delet                         |\n");
	printf("\t\t\t\t\t|5.Quit                          |\n");
	printf("\t\t\t\t\t|--------------------------------|\n");
	return;
}

void studsys() {
	while (1) {
		menu();
		char num = getch();
		switch (num) {
			case '1':
				add(&head, &cur);
				//printf("head = %p\n",head);
				//sleep(1);
				break;
			case '2':
				search(head);
				break;
			case '3':
				list(head);
				break;
			case '4':
				del(&head);
				break;
			case '5':
				return;
				break;
			default:
				printf("\t\t\t\t\t|Press 1~5.\n");
				break;
		}
		printf("\e[1;1H\e[2J"); //clean screen
	}
	return;
}

