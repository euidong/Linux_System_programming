#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

sem_t MUTEX, WRT;
int ReadCount = 0;

int TID[5];

pthread_t WTid[2], RTid[3];

// reader thread.
void *ReaderThread(void *dummy) {
	int randTime = (rand() % 990) + 10;
	usleep(randTime);

	if (sem_wait(&MUTEX) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	if (++ReadCount == 1) { 
		if (sem_wait(&WRT) < 0) {
			perror("sem_wait");
			pthread_exit(NULL);
		}
	}
	if (sem_post(&MUTEX) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}


	printf("Reader %d reading...\n", *(int *)dummy);

	if (sem_wait(&MUTEX) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	
	if (--ReadCount == 0) {
		if (sem_post(&WRT) < 0) {
			perror("sem_post");
			pthread_exit(NULL);
		}
	}

	if (sem_post(&MUTEX) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}
}

// writer thread.
void *WriterThread(void *dummy) {
	int randTime = (rand() % 1000) + 1000;
	usleep(randTime);
	if (sem_wait(&WRT) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}

	printf("Writer %d writing...\n", *(int *)dummy);

	if (sem_post(&WRT) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}
}

// main
void main() {
	int i;
	
	srand(0x8888);

	if (sem_init(&MUTEX, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}

	if (sem_init(&WRT, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}

	for (i =0; i < 2; i++) {
		TID[i] = i;
		if (pthread_create(&WTid[i], NULL, WriterThread, (void *)&TID[i]) < 0) {
			perror("pthread_create");
			exit(1);
		}
	}

	for (i =0; i < 3; i++) {
		TID[i + 2] = i;
		if (pthread_create(&RTid[i], NULL, ReaderThread, (void *)&TID[i+2]) < 0) {
			perror("pthread_create");
			exit(1);
		}
	}	
	
	for (i = 0; i < 2; i++ ) {
		if (pthread_join(WTid[i], NULL) < 0) {
			perror("pthread_join");
			exit(1);
		}
	}

	for (i = 0; i < 3; i++) {
		if (pthread_join(RTid[i], NULL) < 0) {
			perror("pthread_join");
			exit(1);
		}
	}

	if (sem_destroy(&MUTEX) < 0) {
		perror("sem_destroy");
		exit(1);
	}

	if (sem_destroy(&WRT) < 0) {
		perror("sem_destroy");
		exit(1);
	}
}
