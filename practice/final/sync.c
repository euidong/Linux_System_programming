#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NLOOPS 5
#define MAX_BUF 256


/*
	This program make 2 pipe and communication with this.
	One is used to send data from chid to parent. The other is reversation.
*/

char ParentBuf[MAX_BUF];
char ChildBuf[MAX_BUF];

sem_t Mutex;

void *Parent (void *dummy) {
	int i;
	for (i = 0 ; i < NLOOPS; i++) {
		if (sem_wait(&Mutex) < 0)
		{
			perror("sem_wait");
       		pthread_exit(NULL);
   		}

		printf("Parent: Tell to child\n");
		printf("Parent: Wait for child to tell\n");	
		if (sem_post(&Mutex) < 0) {
			perror("sem_post");
			pthread_exit(NULL);
		}
		usleep(1000);
	}
}

void *Child (void *dummy) {
	int i;   
	for (i = 0 ; i < NLOOPS; i++) {
        printf("Child: Wait for parent to tell\n");
		
		if (sem_wait(&Mutex) < 0)
        {
            perror("sem_wait");
            pthread_exit(NULL);
        }

		if (sem_post(&Mutex) < 0) {
            perror("sem_post");
            pthread_exit(NULL);
        }
        printf("Child: Tell to parent\n");
		usleep(1000);
	}
}


void main(){
	int i;
	pthread_t tid[2];

	if (sem_init(&Mutex, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (pthread_create(&tid[0], NULL,(void *)Parent,(void *)NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid[1], NULL, (void *)Child, (void *)NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}	
	for (i = 0; i < 2; i++) {
		if (pthread_join(tid[i], NULL) < 0){
			perror("pthread_join");
			exit(1);		
		}
	}
}
