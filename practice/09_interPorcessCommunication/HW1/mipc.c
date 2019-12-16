#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "synclib.h"

#define NLOOPS 10
#define SIZE sizeof(long)
/*
	This program alterately operate plus 1 by using shared memory. (0 to 10.)
	Especially, this program make shared memory, using /dev/zero file.
    This file is only read 0, and can't be written. But, if you make memory map using this file, you can get shared memory.
*/

// get long pointer value and transform to integer and plus 1.
int update(long *ptr) {
	return ((*ptr)++);
}

void main() {
	int fd, i, counter;
	pid_t pid;
	caddr_t area;

	// open dev/zero file.
	if ((fd = open("/dev/zero", O_RDWR)) < 0) {
		perror("open");
		exit(1);
	}

	// memory mapping dev/zero file. This mean make shared memory.
	if ((area = mmap(0, SIZE, PROT_READ| PROT_WRITE, MAP_SHARED, fd, 0))== (caddr_t) -1) {
		perror("mmap");
		exit(1);
	}

	close(fd);

	// make two pipe
	TELL_WAIT();
	
	// make process
	if((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	// parent process.
	else if (pid > 0) {
		// loop untill i >= 10 
		for (i = 0; i < NLOOPS; i += 2) {
			// update and check wrong data from shared memory.
			if ((counter = update((long *)area)) != i) {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}

			// notice this process operate.
			printf("Parent: counter=%d\n", counter);
			// signal to child process.
			TELL_CHILD();
			// wait when come signal from child.
			WAIT_CHILD();
		}
	}

	// child process.
	else {
		// loop untill i >= 10
		for (i = 1; i <NLOOPS; i += 2) {
			// wait when come signal from parent.
			WAIT_PARENT();
			// update and check wrong data from shared memory.
			if ((counter = update((long *)area)) != i) {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			// notice this process operate.
			printf("Child : counter=%d\n", counter);
			// signal to parent process.
			TELL_PARENT();
		}
	}
}
