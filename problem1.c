#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

void startrandomthread();
void *threads(void*);

sem_t thready;
pthread_t startthread1, startthread2, startthread3;

int allran;
int running[3] = {0, 0, 0};
int resource;

int main() {
	allran = 0;
	resource = 0;
	srand(time(NULL));
	sem_init(&thready, 0, 1);
	pthread_create(&startthread1, NULL, threads, (void *)1);
	pthread_create(&startthread2, NULL, threads, (void *)2);
	pthread_create(&startthread3, NULL, threads, (void *)3);
	int started = 1;
	while (1) {
		if (allran == 3) {
			if (started == 1) {
				printf("\e[1;33mAll Threads Started!"
					" Shared Resource = %d\e[0m\n", resource);
				started = 0;
			}
			if ((running[0] == 0) && (running[1] == 0) && (running[2] == 0)) {
				printf("\e[1;32mAll Threads Completed!"
					" Shared Resource = %d\e[0m\n", resource);
				allran = 0;
				started = 1;
			}
		}
	}
	sem_destroy(&thready);
	return 0;
}


void *threads(void *arg) {
	while(1) {
		if (allran != 3) {
			allran++;
			int value = arg;
			running[value] = 1;
			int timeout = (rand() % 8) + 1;
			printf("Starting Thread \e[1;36m%d\e[0m "
			 "for \e[1;36m%d\e[0m seconds...\n", arg, timeout);
			sleep(timeout);
			resource++;
			printf("Thread \e[1;36m%d\e[0m Completed!\n", arg);
			running[value] = 0;
		}
	}
}

