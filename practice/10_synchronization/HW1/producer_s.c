#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "semlib.h"
#include "prodcons.h"
/*
	This progrma make producer that produce data in memory that shared with consumer.
	When two or more process use shared memory, shared memory must keep synchronization.
	So, this program implement this with semaphore.(System V with custom library)
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

	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *)-1) {
		perror("shmat");
		exit(1);
	}
	
	// make 3 semaphore with key.
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

	srand(0x8888);


	for (i = 0; i < NLOOPS; i++) {
		// semaphore check is buffer full.
		if (semWait(emptySemid) < 0 ) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
	
		// semaphore check is buffer mutual exclusion.
		if (semWait(mutexSemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		
		// produce data to buffer.
		printf("Producer: Producing an item.....\n");
		data = (rand() % 100) * 10000;
		pBuf->buf[pBuf->in].data = data;
		pBuf->in = (pBuf->in + 1) % MAX_BUF;
		pBuf->counter++;

		// signal to mutex semaphore.
		if (semPost(mutexSemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}

		// signal to full semaphore.
		if (semPost(fullSemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		// sleep a little time.
		usleep(data);
	}

	printf("Producer: Produced %d items.....\n", i);
	
	sleep(2);
	printf("Producer: %d items in buffer......\n", pBuf->counter);


	// Destory all semaphore and shared memory.
	if (semDestroy(emptySemid) < 0) {
		fprintf(stderr, "semDestroy failure\n");
	}

	if (semDestroy(fullSemid) < 0) {
		fprintf(stderr, "semDestroy failure\n");
	}

	if (semDestroy(mutexSemid) < 0) {
		fprintf(stderr, "semDestroy failure\n");
	}

	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl");
		exit(1);
	}
}
