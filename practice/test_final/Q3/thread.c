#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

char msg[100];
sem_t sem;

void *getMsgThread(void *dummy) {
	if (sem_wait(&sem) < 0) {
		perror("sem_wait");
		exit(1);
	}
	printf("%s\n", msg);
}


void main() {
	pthread_t tid;
	
	if (sem_init(&sem, 0, 0) < 0) {
		perror("sem_init");
		exit(1);
	}

	if (pthread_create(&tid, NULL, getMsgThread, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	sprintf(msg, "hello");
	
	if (sem_post(&sem) < 0) {
		perror("sem_post");
		exit(1);
	}

	if (pthread_join(tid, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}
	
}
