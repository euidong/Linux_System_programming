#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"

void main() {
	int fd;
	char buf[MAX_BUF];
	if ((fd = open(SERV_FIFO, O_RDWR)) < 0) {
		perror("open");
		exit(1);
	}

	sprintf(buf, "Hello");
	if (write(fd, buf, sizeof(buf)) < 0) {
		perror("write");
		exit(1);
	}
	printf("FIFO2: Sent a message: %s\n", buf);

	if (read(fd, buf, sizeof(buf)) < 0) {
		perror("read");
		exit(1);
	}

	printf("FIFO2: Received a message: %s\n", buf);
	
	if (close(fd) < 0) {
		perror("close");
		exit(1);
	}	
}
