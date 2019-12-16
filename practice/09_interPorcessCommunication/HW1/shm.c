#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE (SHM_R | SHM_W)

char Array[ARRAY_SIZE];

/*
	This program check how memory space allocated.
	First, global variable "Array" is allocated data area.
	Second, local variable "shmid" is allocated stack area.
	Third, dynamic allocated variable is allocated heap area(extra area).
	Forth, shared memory variable is allocated extra area.(is between heap and stack)
*/
void main() {
	int shmid;
	char *ptr, *shmptr;

	if ((ptr = (char *)malloc(MALLOC_SIZE)) == NULL) {
		perror("malloc");
		exit(1);
	}

	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget");
		exit(1);
	}

	if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}

	printf("Array[] from %p to %p\n" , &Array[0], &Array[ARRAY_SIZE]);
	printf("Stack around %p\n", &shmid);
	printf("Malloced from %p to %p\n", ptr, ptr+MALLOC_SIZE);
	printf("Shared memory attached from %p to %p\n", shmptr, shmptr+SHM_SIZE);

	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl");
		exit(1);
	}
}

