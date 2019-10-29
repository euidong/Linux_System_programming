/*
This program change current directory in process.
So, when this program terminated, return to previous location.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void main(int argc, char *argv[]) {
	//check arg count.
	if (argc != 2) {
		printf("Usage: %s destination",argv[0]);
		exit(1);
	}
	
	//change directory.
	if (chdir(argv[1]) < 0) {
		perror("chdir");
		exit(1);
	}

}
