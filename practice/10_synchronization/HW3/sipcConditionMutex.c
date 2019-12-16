#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
pthread_mutex_t mutex;
pthread_cond_t turn1;
pthread_cond_t turn2;

void *sipc1(void *dummy) {
	int tid = *(int *)dummy;

	if (pthread_mutex_lock(&mutex) < 0) {
		perror("pthred_mutex_lock");
		pthread_exit(NULL);
	}
	
	if (pthread_cond_wait(&turn1, &mutex) < 0) {
		perror("pthread_cond_wait");
		pthread_exit(NULL);
	}

	printf("Received request: %s\n", Buf);
	
	sprintf(Buf, "This is a reply from %d", tid);
	printf("Replied.\n");
	
	if (pthread_cond_signal(&turn2) < 0) {
		perror("pthread_cond_signal");
		pthread_exit(NULL);
	}
	if (pthread_mutex_unlock(&mutex) < 0) {
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}
}

void *sipc2(void *dummy) {
	int tid = *(int *)dummy;
	if (pthread_mutex_lock(&mutex) < 0) {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	sprintf(Buf, "This request from %d,", tid);
	printf("Send a request.....\n");

	if (pthread_cond_signal(&turn1) < 0) {
		perror("pthread_cond_signal");
		pthread_exit(NULL);
	}

	if (pthread_cond_wait(&turn2, &mutex) < 0) {
		perror("pthraed_cond_wait");
		pthread_exit(NULL);
	}
	
	printf("Received reply: %s\n", Buf);

	if (pthread_mutex_unlock(&mutex) < 0) {
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}
}

void main() {
	pthread_t tid1, tid2;
	Buf[0] = '2';	
	if (pthread_mutex_init(&mutex, NULL) < 0) {
		perror("pthread_mutex_init");
		exit(1);
	}
	
	if (pthread_cond_init(&turn1, NULL) < 0) {
		perror("pthread_cond_init");
		exit(1);
	}
	if (pthread_cond_init(&turn2, NULL) < 0) {
		perror("pthread_cond_init");
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

	if (pthread_mutex_destroy(&mutex) < 0) {
		perror("pthread_mutex_destroy");
	}

	if (pthread_cond_destroy(&turn1) < 0) {
		perror("pthread_cond_destroy");
	}

	if (pthread_cond_destroy(&turn2) < 0) {
		perror("pthread_cond_destroy");
	}
}
