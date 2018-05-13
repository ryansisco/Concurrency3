#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

void datap();
void status();
void choose();
void add(int, int);
void rem(int);
int search(int);
int listsize();

int searchers_c;
char choice[30];

struct Node {
	int data;
	struct Node* next;
}*head;

int main() {
	srand(time(NULL));
	system("clear");
	struct node *head;
	while(1) {
		datap();
		status();
		choose();
	}
	//loop
	//loop
	return 0;
}

void datap() {
	//prints table of what's going on
	system("clear");
	printf("\e[1;30mo---------------------------------------o\e[0m\n");
	printf("\e[1;30m|\e[0m");
	printf(" Searchers:  \e[1;36m%5d\e[0m ", searchers_c);
	printf("\e[1;30m|\e[0m");
	printf(" List Size:  \e[1;36m%5d\e[0m ", listsize());
	printf("\e[1;30m|\e[0m\n");
}

void status() {
	if (strcmp(choice, "deleted") == 0) {
		printf("\e[1;30m|\e[0m");
		printf("\e[1;31m Deleted Item\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "added") == 0) {
		printf("\e[1;30m|\e[0m");
		printf("\e[1;32m Added Item\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "search") == 0) {
		printf("\e[1;30m|\e[0m");
		printf("\e[1;35m Searching\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "build") == 0) {
		printf("\e[1;30m|\e[0m");
		printf("\e[1;37m Building...\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "error") == 0) {
		printf("\e[1;30m|\e[0m");
		printf("\e[1;33m Invalid Syntax\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strstr(choice, "found")) {
		return 0;
	}
	if (strcmp(choice, "print") == 0) {
		int i;
		int y;
		struct Node *n;
		n = head;
		printf("\e[1;30m|\e[0m");
		for (i = 0; i < listsize(); i++) {
			if ((i % 5 == 0) && (i > 0))  {
				printf("\e[1;30m\t| \n\e[0m");
				printf("\e[1;30m|\e[0m");
			}
			printf("%6d ", n->data);
			n = n->next;
		}

		for (y = 0; y < (5 - (i % 5) + 1); y++) {
			if (i == 0) {
				printf("\e[1;30m\t\t\t\t\t\e[0m");
				break;
			}
			if ((i % 5) == 0) {
				printf("\t");
				break;
			}
			if ((i % 5) == 1) {
				printf("\t\t\t\t");
				break;
			}
			printf("\t");
		}
		printf("\e[1;30m|\e[0m");
		printf("\n\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	printf("\e[1;30m|\t\t\t\t\t|\e[0m\n");
	printf("\e[1;30mo---------------------------------------o\e[0m\n");
}

void choose() {
	fgets(choice, 50, stdin);
	if (strstr(choice, "add ")) {
		int myVar = 0;
		int iter = 0;
		int neg = 0;
		int confirm = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				if (choice[iter-1] == '-') {
					neg = 1;
				}
				myVar = 10 * myVar + (choice[iter]-'0');
				confirm = 1;
			}
		}
		if (neg == 1) {
			myVar = myVar*-1;
		}
		if (confirm == 0) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			//listsize++;
			strcpy(choice, "added");
			add(myVar, 1);
		}
		return;
	}
	if (strstr(choice, "del ")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				myVar = 10 * myVar + (choice[iter]-'0');
			}
		}
		if (myVar <= 0) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			if ((listsize() != 0) && (listsize() >= myVar)){
				//if list isnt empty
				rem(myVar);
				strcpy(choice, "deleted");
			}
		}
		return;
	}
	if (strstr(choice, "find ")) {
		int myVar = 0;
		int iter = 0;
		int neg = 0;
		int confirm = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				if (choice[iter-1] == '-') {
					neg = 1;
				}
				myVar = 10 * myVar + (choice[iter]-'0');
				confirm = 1;
			}
		}
		if (neg == 1) {
			myVar = myVar*-1;
		}
		if (confirm == 0) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			if (listsize() != 0) {
				//if list isnt empty
				strcpy(choice, "search");
				searchers_c++;
				sleep(1);
				if (search(myVar) != -1) {
					printf("\e[1;30m|\e[0m");
					printf("\e[1;33m Found Value %5d    at Position %d\e[0m",
						myVar, search(myVar));
					printf("\t\e[1;30m|\e[0m\n");
					printf("\e[1;30mo---------------------------------------o\e[0m\n");
					strcpy(choice, "found");
				}
				else {
					printf("\e[1;30m|\e[0m");
					printf("\e[1;33m Couldn't Find Value %5d\e[0m",
						myVar);
					printf("\t\t\e[1;30m|\e[0m\n");
					printf("\e[1;30mo---------------------------------------o\e[0m\n");
					strcpy(choice, "found");
				}
				searchers_c--;
			}
		}
		return;
	}
	if (strstr(choice, "build ")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				myVar = 10 * myVar + (choice[iter]-'0');
			}
		}
		if (myVar <= 0) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			strcpy(choice, "build");
			int i;
			int myVal;
			//start building singly linked list
			for (i = 0; i < myVar; i++) {
				myVal = rand() % 1000;
				add(myVal, 1);
			}
		}
		return;
	}
	if (strstr(choice, "print")) {
		strcpy(choice, "print");
		return;
	}
	if (strstr(choice, "exit")) {
		exit(0);
	}
	else {
		strcpy(choice, "");
	}
}

void add(int value, int fill) {
	int i;
	listsize();
	struct Node *n;
	if (head == NULL) {
		n = (struct Node *)malloc(sizeof(struct Node));
		head = n;
		head->data = value;
		head->next = NULL;
		fill--;
	}
	struct Node *e = head;
	int a = 0;
	for (i = 0; i < fill; i++) {
		n = (struct Node *)malloc(sizeof(struct Node));
		while(e->next != NULL) {
			e = e->next;
			a++;
		}
		e->next = n;
		n->data = value;
		n->next = NULL;
	}
}

void rem(int value) {
	int i;
	struct Node *bad;
	struct Node *l;
	struct Node *r;
	bad = head;
	for (i = 0; i < value-1; i++) {
		l = bad;
		bad = bad->next;
		r = bad->next;
	}
	if (bad == head) {
		head = bad->next;
		free(bad);
		return;
	}
	if (r != NULL) {
		l->next = r;
		free(bad);
		return;
	}
	l->next = NULL;
	free(bad);
}

int search(int value) {
	struct Node *n;
	n = head;
	int iter = 0;
	int pos = 0;
	int confirm = 0;
	while(n != NULL) {
		iter++;
		if (n->data == value) {
			pos = iter;
			confirm = 1;
			break;
		}
		n = n->next;
	}
	if (confirm == 0) {
		return -1;
	}
	return pos;
}

int listsize() {
	struct Node *n;
	n = head;
	int iter = 0;
	while(n != NULL) {
		n = n->next;
		iter++;
	}
	return iter;
}
