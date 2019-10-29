#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/*
This program make file has 1023 empty bit + '\0'

First, it create file.hole by 400 . if this file can't create print error and exit from this program. 

Second, it seek location on start of file.hole + 1023 offset. if this file can't seek print error and exit from this program.

Third, it write '\0' to file.hole's 1024 location.
*/

void main() {
	int fd;
	char ch = '\0';

	if ((fd = creat("file.hole", 0400)) < 0) {
		perror("creat");
		exit(1);
	}

	if (lseek(fd, 1023, SEEK_SET) < 0) {
		perror("lseek");
		exit(1);
	}

	write(fd, &ch, 1);

	close(fd);
}
