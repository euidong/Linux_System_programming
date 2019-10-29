/*
This program make SIGINT handler.
Ant this handler cancel thread except main thread.
and wait untill all thread is done.
Because, thread may set cancel disable or deferred.

And, all thread set cancel type = asynchronized, state = enable 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
pthread_t tid[2];

void SigIntHandler(int sigNo) {
	int i;
	for (i =0 ; i < 2; i++) {
		if (pthread_cancel(tid[i])) {
			perror("pthread_cancel");
			exit(1);
		}
	}
	for (i =0; i < 2; i++) {
		if (pthread_join(tid[i], NULL)) {
			perror("pthread_join");
			exit(1);
		}
	}
	printf("Threads terminated: tid=%ld, %ld\n", tid[0], tid[1]);
	exit(0);
}

void Thread1(void* dummy) {
	printf("Thread %ld created.....\n", pthread_self());

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}
	
	while(1)
		;
}

void Thread2(void* dummy) {
    printf("Thread %ld created.....\n", pthread_self());

    if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) {
        perror("pthread_setcancelstate");
        pthread_exit(NULL);
    }
    if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) {
        perror("pthread_setcanceltype");
        pthread_exit(NULL);
    }

    while(1)
        ;	
}

void main () {
	if (pthread_create(&tid[0], NULL, (void *)Thread1, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid[1], NULL, (void *)Thread2, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	signal(SIGINT, SigIntHandler);
	
	printf("Press Ctrl + C to quit\n");
	for ( ; ; )
		pause();
}
