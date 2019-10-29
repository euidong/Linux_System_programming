/*
This program make direcory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc, char *argv[]){
	
	// user didn't put directory name or put argc > 2.
	if (argc != 2) {
		printf("Usage: %s directory", argv[0]);
		exit(1);
	}
	
	// make a directory had authentication 755.
	if (mkdir(argv[1], 0755) < 0) {
		perror("mkdir");
		exit(1);
	}
}
