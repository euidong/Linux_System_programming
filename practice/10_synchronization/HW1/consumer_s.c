#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "semlib.h"
#include "prodcons.h"
/*
	This program make consumer that consum data in buffer shared with producer.
    When two or more process shared memory, it must ensured synchronization.
	So, this program ensure that with semaphore.(System V with custom library.)	
*/
void main() {
	BoundedBufferType *pBuf;
	int shmid, i, data;
	int emptySemid, fullSemid, mutexSemid;
	
	// make and attach shared memory.
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget");
		exit(1);
	}

	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}

	// make 3 semaphore.
	if ((emptySemid = semInit(EMPTY_SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if ((fullSemid = semInit(FULL_SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	// initialize 3 semaphore's value.
	if (semInitValue(emptySemid, MAX_BUF) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if (semInitValue(fullSemid, 0) < 0) {
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}

	if (semInitValue(mutexSemid, 1) < 0) {
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}

	for (i = 0; i < NLOOPS; i++) {
		// check this buffer is empty.
		if (semWait(fullSemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		
		// check this buffer is mutual exclusive.
		if (semWait(mutexSemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		
		// consum data.
		printf("Consumer: Consuming an item.....\n");
		data = (rand() %100) * 10000;
		data = pBuf->buf[pBuf->out].data;
		pBuf->out = (pBuf->out + 1) % MAX_BUF;
		pBuf->counter--;

		// signal to mutex semaphore.
		if (semPost(mutexSemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}

		// signal to empty semaphore.
		if (semPost(emptySemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		// sleep a little time.
		usleep(data);
	}

	printf("Consumer: Consumed %d items......\n", i);

	sleep(2);
	printf("Consumer: %d items in buffer.....\n", pBuf->counter);

	if (semDestroy(emptySemid) < 0)
		fprintf(stderr, "semDestroy failure\n");
	if (semDestroy(fullSemid) < 0)
		fprintf(stderr, "semDestroy failure\n");
	if (semDestroy(mutexSemid) < 0)
		fprintf(stderr, "semDestroy failure\n");
	if (shmctl(shmid, IPC_RMID, 0) < 0){
		perror("shmctl");
		exit(1);
	}
}
