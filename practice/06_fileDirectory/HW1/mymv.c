/*
This program do renaming.
*/

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]) {
	// source & destination is required
	if (argc != 3) {
		printf("Usage: %s source destination \n", argv[0]);
		exit(1);
	}
	// renaming argv[1] filename to argv[2]
	if(rename(argv[1], argv[2]) < 0) {
		perror("rename");
		exit(1);
	}
}
