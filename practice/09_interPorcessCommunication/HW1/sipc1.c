#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"

/*
	This program make a shared memory and wait when request come.
	This request can check by busy wait.(it look at between first and first+4(sizeof(int))
	When this part(indexer) changed to 1. it means that the request is come.
	So, busy wait lock is done, then get message.
	And, make response to requester. Additionaly, change part of indexer to 0.
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

	// get shared memory in process.
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}

	// the first part is indexer.
	// 1 is my turn.
	// 0 is requester turn.
	pInt = (int *)ptr;

	// busy waiting
	// 20~60 milli seconds
	while ((*pInt) == 0)
		;

	// get data except indexer part.
	pData = ptr + sizeof(int);
	printf("Received request: %s......", pData);
	
	// change contents to send requester.
	sprintf(pData, "This is a reply from %d", getpid());
	
	// notice to requester.
	*pInt = 0;
	printf("Replied.\n");

	sleep(1);

	// remove shared memory.
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl");
		exit(1);
	}
}
