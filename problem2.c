#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

void datap();
void status(int);
void choose();
void *add(void*);
void *rem(void*);
void *search(void*);
int listsize();

int searchers_c;
char choice[30];
int newprompt;
int foundit[3];

sem_t Searcherthread1;
sem_t adderthread1;
sem_t remthread1;

struct Node {
	int data;
	struct Node* next;
}*head;

int main() {
	srand(time(NULL));
	system("clear");
	struct node *head;
	while(1) {
		if (newprompt == 0) {
			datap();
			status(0);
		}
		if (newprompt == 1) {
			datap();
			status(1);
			newprompt = 0;
		}
		choose();
	}
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

void status(int op) {
	if (op == 1) {	//prints if data was searched
		if (foundit[0]) {
			printf("\e[1;35m  Found Value %5d    Position %5d\e[0m",
				foundit[1], foundit[2]);
			printf("\n\e[1;30mo---------------------------------------o\e[0m\n");
			strcpy(choice, "found");
		}
		else {
			printf("\e[1;35m Couldn't Find Value %5d\e[0m",
				foundit[1]);
			printf("\n\e[1;30mo---------------------------------------o\e[0m\n");
			strcpy(choice, "found");
		}
		return 0;
	}
	if (strcmp(choice, "deleted") == 0) {	//prints command
		printf("\e[1;30m|\e[0m");
		printf("\e[1;31m Deleted Item\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "added") == 0) {	//prints command
		printf("\e[1;30m|\e[0m");
		printf("\e[1;32m Added Item\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "build") == 0) {	//prints command
		printf("\e[1;30m|\e[0m");
		printf("\e[1;37m Building...\t\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "error") == 0) {	//prints command
		printf("\e[1;30m|\e[0m");
		printf("\e[1;33m Invalid Syntax\t\t\t\e[0m");
		printf("\e[1;30m|\e[0m\n");
		printf("\e[1;30mo---------------------------------------o\e[0m\n");
		return 0;
	}
	if (strcmp(choice, "print") == 0) {	//prints entire data table
		int i;
		int y;
		struct Node *n;
		n = head;
		printf("\e[1;30m|\e[0m");
		for (i = 0; i < listsize(); i++) {	//for list size
			if ((i % 5 == 0) && (i > 0))  {	//breaks in 5s
				printf("\e[1;30m\t| \n\e[0m");
				printf("\e[1;30m|\e[0m");
			}
			printf("%6d ", n->data);
			n = n->next;
		}

		for (y = 0; y < (5 - (i % 5) + 1); y++) { //table organize
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
	fgets(choice, 50, stdin); //gets commands
	if (strstr(choice, "add ")) {
		int myVar = 0;
		int iter = 0;
		int neg = 0;
		int confirm = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) { //gets number after command
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
		else {	//starts thread
			//do it
			strcpy(choice, "added");
			sem_init(&adderthread1, 0, 1);
			pthread_t adderthread;
			pthread_create(&adderthread, NULL, add, (void *)myVar);
			pthread_join(adderthread, NULL);
			sem_destroy(&adderthread1);
		}
		return;
	}
	if (strstr(choice, "del ")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) { //gets number after command
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
			if ((listsize() != 0) && (listsize() >= myVar)){	//starts thread
				//if list isnt empty
				sem_init(&remthread1, 0, 1);
				sem_wait(&remthread1);
				pthread_t remthread;
				pthread_create(&remthread, NULL, rem, (void *)myVar);
				pthread_join(remthread, NULL);
				sem_destroy(&remthread1);
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
		for (iter = 0; iter < strlen(choice)-1; iter++) { //gets number after command
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
			if (listsize() != 0) {	//starts thread
				//if list isnt empty
				searchers_c++;
				sem_init(&Searcherthread1, 0, 1);
				pthread_t Searcherthread;
				pthread_create(&Searcherthread, NULL, search, (void *)myVar);
				pthread_join(Searcherthread, NULL);
				sem_destroy(&Searcherthread1);
				searchers_c--;
			}
		}
		return;
	}
	if (strstr(choice, "build ")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) { //gets number after command
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
			for (i = 0; i < myVar; i++) {	//starts thread
				myVal = rand() % 1000;
				sem_init(&adderthread1, 0, 1);
				sem_wait(&adderthread1);
				pthread_t adderthread;
				pthread_create(&adderthread, NULL, add, (void *)myVal);
				pthread_join(adderthread, NULL);
				sem_destroy(&adderthread1);
			}
		}
		return;
	}
	if (strstr(choice, "print")) {
		strcpy(choice, "print"); //eliminates \n
		return;
	}
	if (strstr(choice, "exit")) {
		exit(0);
	}
	else {
		strcpy(choice, "");
	}
}

void* add(void* value) {	//adds data to the linked list
	int fill = 1;
	int i;
	listsize();
	struct Node *n;
	if (head == NULL) {	//makes a new head
		n = (struct Node *)malloc(sizeof(struct Node));
		head = n;
		head->data = value;
		head->next = NULL;
		fill--;
	}
	struct Node *e = head;
	int a = 0;
	for (i = 0; i < fill; i++) { //fills outside head
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

void *rem(void* value) {	//removes item
	int i;
	struct Node *bad;
	struct Node *l;
	struct Node *r;
	bad = head;
	for (i = 0; i < value-1; i++) { //gets position in list
		l = bad;
		bad = bad->next;
		r = bad->next;
	}
	if (bad == head) {	//if head
		head = bad->next;
		free(bad);
		return;
	}
	if (r != NULL) {	//if at the end
		l->next = r;
		free(bad);
		return;
	}
	l->next = NULL;
	free(bad);
}

void *search(void *arg) {	//searches list
	foundit[1] = arg;
	newprompt = 1;
	int value = arg;
	struct Node *n;
	n = head;
	int iter = 0;
	int pos = 0;
	int confirm = 0;
	while(n != NULL) {	//if no head
		iter++;
		if (n->data == value) {
			pos = iter;
			confirm = 1;
			foundit[0] = 1;
			foundit[2] = pos;
			break;
		}
		n = n->next;
	}
	if (confirm == 0) {
		foundit[0] = 0;
	}
}

int listsize() {	//gets list size
	struct Node *n;
	n = head;
	int iter = 0;
	while(n != NULL) {
		n = n->next;
		iter++;
	}
	return iter;
}
