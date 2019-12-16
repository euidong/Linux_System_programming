#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"

void main() {
	int fd;
	char msg[MAX_BUF];
	
	if (mkfifo(SERV_FIFO, 0600) < 0) {
		perror("mkfifo");
		exit(1);
	}

	if ((fd = open(SERV_FIFO, O_RDWR)) < 0) {
		perror("open");
		exit(1);
	}

	if (read(fd, (char *)&msg, sizeof(msg)) < 0) {
		perror("read");
		exit(1);
	}
	printf("FIFO1: Received a message: %s\n", msg);

	sprintf(msg, "Hi");
	
	if (write(fd, (char *)&msg, sizeof(msg)) < 0) {
		perror("write");
		exit(1);
	}

	printf("FIFO1: Sent a message: %s\n", msg);
	fflush(stdout);
	sleep(1);
	
	if (close(fd) < 0) {
		perror("close");
	}

	if (remove(SERV_FIFO) < 0) {
		perror("remove");
		exit(1);
	}
}
