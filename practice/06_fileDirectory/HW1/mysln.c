/*
This program make symbolic link file put by user. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
	//check arg count.
	if (argc != 3) {
		printf("Usage: %s source destination", argv[0]);
		exit(1);
	}
	
	//make symbolic link file.
	if (symlink(argv[1], argv[2]) < 0) {
		perror("symlink");
		exit(1);
	}
}

