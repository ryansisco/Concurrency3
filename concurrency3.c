#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

void clean(int);
void create(int);
void datap();
void status();
void choose();

int searchers_c;
int listsize;
char choice[30];

sem_t inserter;
sem_t deleter;

int main() {
	system("clear");
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
	printf("-----------------------------------\n");
	printf("| Searchers:  \e[1;36m%2d\e[0m | List Size:  \e[1;36m%2d\e[0m |\n", 
		searchers_c, listsize);
}

void create(int num) {
	//create semaphores
}

void clean(int num) {
	//delete semaphores
}

void status() {
	if (strcmp(choice, "deleted") == 0) {
		printf("|\e[1;31m Deleted Item\t\t\t  \e[0m|\n");
		printf("-----------------------------------\n");
		return 0;
	}
	if (strcmp(choice, "added") == 0) {
		printf("|\e[1;32m Added Item\t\t\t  \e[0m|\n");
		printf("-----------------------------------\n");
		return 0;
	}
	if (strcmp(choice, "search") == 0) {
		printf("|\e[1;35m Searching\t\t\t  \e[0m|\n");
		printf("-----------------------------------\n");
		return 0;
	}
	if (strcmp(choice, "build") == 0) {
		printf("|\e[1;37m Building...\t\t\t  \e[0m|\n");
		printf("-----------------------------------\n");
		return 0;
	}
	if (strcmp(choice, "error") == 0) {
		printf("|\e[1;33m Invalid Syntax\t\t  \e[0m|\n");
		printf("-----------------------------------\n");
		return 0;
	}
	printf("|\t\t\t\t  |\n");
	printf("-----------------------------------\n");
}

void choose() {
	fgets(choice, 50, stdin);
	if (strstr(choice, "add")) {
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
			listsize++;
			strcpy(choice, "added");
		}
		return;
	}
	if (strstr(choice, "del")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				myVar = 10 * myVar + (choice[iter]-'0');
			}
		}
		if (isdigit(myVar)) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			if ((listsize != 0) && (listsize >= myVar)){
				//if list isnt empty
				listsize--;
				strcpy(choice, "deleted");
			}
		}
		return;
	}
	if (strstr(choice, "find")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				myVar = 10 * myVar + (choice[iter]-'0');
			}
		}
		printf("%d\n", myVar );
		if (isdigit(myVar)) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			if (listsize != 0) {
				//if list isnt empty
				strcpy(choice, "search");
				searchers_c++;
				//start searching...
				//searchers_c--;
			}
		}
		return;
	}
	if (strstr(choice, "build")) {
		int myVar = 0;
		int iter = 0;
		for (iter = 0; iter < strlen(choice)-1; iter++) {
			if (isdigit(choice[iter])) {
				myVar = 10 * myVar + (choice[iter]-'0');
			}
		}
		if (isdigit(myVar)) {
			//if not a digit
			strcpy(choice, "error");
		}
		else {
			//do it
			strcpy(choice, "build");
			int i;
			printf("myVar = %d\n", myVar);
			//start building singly linked list
			for (i = 0; i < myVar; i++) {
				listsize++;
			}
		}
		return;
	}
	if (strstr(choice, "exit")) {
		exit(0);
	}
	else {
		strcpy(choice, "");
	}
}