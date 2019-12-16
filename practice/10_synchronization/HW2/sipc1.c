#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include "semlib.h"

void main() {
	int shmid;
	char *ptr;
	int *pInt;
	int sema;

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

	if ((sema = semInit(SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if (semInitValue(sema, 0) < 0) {
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}

	if (semWait(sema) < 0) {
		fprintf(stderr, "semWait failure\n");
		exit(1);
	}

	// get data except indexer part.
	printf("Received request: %s......", ptr);
	
	// change contents to send requester.
	sprintf(ptr, "This is a reply from %d", getpid());

	if (semPost(sema) < 0) {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	// notice to requester.
	printf("Replied.\n");

	sleep(1);

	if (semDestroy(sema) < 0)
		fprintf(stderr, "semDestroy failure\n");

	// remove shared memory.
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl");
		exit(1);
	}
}
