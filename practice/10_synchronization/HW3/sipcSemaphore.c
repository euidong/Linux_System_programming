#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_BUF 100
/*
    sipc1
    1. waiting request
    2. when come request, print request and response

    sipc2
    1. request to sipc1
    2. waiting response
    3. when come response, print response.
*/

char Buf[MAX_BUF];
sem_t turn1, turn2;


void *sipc1(void *dummy) {
	int tid = *(int *)dummy;
	
	if (sem_wait(&turn1) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}

	printf("Received request: %s", Buf);
	sprintf(Buf, "This is a reply from %d\n", tid);
	
	if (sem_post(&turn2) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}
	
	printf("Replied\n");
	
}

void *sipc2(void *dummy) {
	int tid = *(int *)dummy;
	printf("Send a request......\n");
	sprintf(Buf, "This request from %d\n", tid);
	if (sem_post(&turn1) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}

	if (sem_wait(&turn2) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	printf("Received reply:%s", Buf);
}

void main() {
	pthread_t tid1, tid2;
	if (sem_init(&turn1,0,0) < 0) {
		perror("sem_init");
		exit(1);
	}
	
	if (sem_init(&turn2,0,0) < 0) {
		perror("sem_init");
		exit(1);
	}

	if (pthread_create(&tid1, NULL, (void *)sipc1, (void *)&tid1) < 0) {
		perror("pthread_create");
		exit(1);	
	}

	if (pthread_create(&tid2, NULL, (void *)sipc2, (void *)&tid2) < 0) {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_join(tid1, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}

	if (pthread_join(tid2, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}

	if (sem_destroy(&turn1) < 0) {
		perror("sem_destroy");
	}

	if (sem_destroy(&turn2) < 0) {
		perror("sem_destroy");
		exit(1);
	}
}
