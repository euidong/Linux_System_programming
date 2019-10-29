/*
This program make link file. (Hard link)
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
	// check arg count
	if (argc != 3) {
		printf("Usage : %s source destination \n", argv[0]);
		exit(1);
	}
	
	// make hard link file.
	if(link(argv[1], argv[2]) < 0) {
		perror("link");
		exit(1);
	}
}
