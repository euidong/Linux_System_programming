#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "prodcons.h"
/*
    This program consum data to buffer that is memory shared with producer.
    First, make Shared memory.
    Second, attach buffer to memory.
    Third, consum data to buffer 20 times.(if buffer is empty, wait)
*/

void main() {
	BoundedBufferType *pBuf;
	int shmid, i, data;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget");
		exit(1);
	}

	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *)-1) {
		perror("shmat");
		exit(1);
	}

	for (i = 0; i < NLOOPS; i++) {
		if (pBuf->counter == 0) {
			printf("Consumer: Buffer empty. Waiting.....\n");
			while(pBuf->counter == 0)
				;
		}
		printf("Consumer: Consuming an item....\n");
		data = pBuf->buf[pBuf->out].data;
		pBuf->out = (pBuf->out + 1) % MAX_BUF;
		pBuf->counter--;

		usleep(data);
	}
	
	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer ......\n", pBuf->counter);
}
