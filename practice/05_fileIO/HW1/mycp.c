#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 1024

/*
this file want to implement linux command "cp"


First, this program check whether user put 3 argv. if not print error message and exit this program.

Second, this program open read file argv[1]. if can't open it, print error message and exit this program.

Third, this program open write file argv[2]. if can't open it, print error message and exit this program.

Fourth, this program read data from argv[1] untill this argv[1]'s end of file or this file has error. and write this data to argv[2].
*/

void main(int argc, char *argv[]) {
	int fd1, fd2, count;
	char buf[MAX_BUF];

	if (argc != 3) {
		printf("Useage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((fd1 = open(argv[1], O_RDONLY)) < 0 ) {
		perror("open");
		exit(1);
	}
	
	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC)) < 0) {
		perror("open");
		exit(1);
	}

	while((count = read(fd1, buf, MAX_BUF)) > 0) {
		write(fd2, buf, count);
	} 
	
	close(fd1);
	close(fd2);
}
