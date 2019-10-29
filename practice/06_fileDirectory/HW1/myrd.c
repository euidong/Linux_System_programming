/*
This program remove directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
	//check arg count
	if (argc == 1){
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
	
	// remove directory
	for (int i = 1; i < argc ; i++) {
		if(rmdir(argv[i]) < 0){
			perror("rmdir");
			exit(1);
		}
		else
			printf("remove : %s\n", argv[i]);
	}
}
