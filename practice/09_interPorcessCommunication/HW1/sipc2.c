#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
/*
	This program sent message and get response.
	First, it make or get address of shared memory.
	Second, it load shared memory to process.
	Third, set message to shared memory and notice by making indexer part to 1.
	Forth, wait when indexer change to 0.(busy waiting)
	Fifth, printing response from sender.
*/
void main() {
	int shmid;
	char *ptr, *pData;
	int *pInt;

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

	pInt = (int *)ptr;
	pData = ptr + sizeof(int);

	// set message.
	sprintf(pData, "This is request from %d.", getpid());
	
	// notice to sender.
	*pInt = 1;
	printf("Sent a request.....");
	
	// wait when pInt changed to 0.
	while(*pInt == 1)
		;

	printf("Received reply: %s\n", pData);
}

