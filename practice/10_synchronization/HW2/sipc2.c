#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include "semlib.h"

void main() {
	int shmid, sema;
	char *ptr, *pData;

	// make shared memory.
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget");
		exit(1);
	}
	
	// get shared memory.
	if ((ptr = shmat(shmid, 0, 0)) ==(void *)-1) {
		perror("shmat");
		exit(1);
	}

	if ((sema = semInit(SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	// set message.
	sprintf(ptr, "This is request from %d.", getpid());
	
	// notice to sender.
	printf("Sent a request.....");
	
	if (semPost(sema) < 0) {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	sleep(1);

	if (semWait(sema) < 0) {
		fprintf(stderr, "semWait failure\n");
		exit(1);
	}	
	printf("Received reply: %s\n", ptr);
}

