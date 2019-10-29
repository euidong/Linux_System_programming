/*
This program handle exit station.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myexit1() {
	printf("first exit handler\n");
}

void myexit2() {
	printf("second exit handler\n");
}

void main() {
	// add exit handler 
	// hamdler's action is processed LIFO
	if (atexit(myexit1) != 0) {
		perror("atexit");
		exit(1);
	}
	if (atexit(myexit2) != 0) {
		perror("atexit");
		exit(1);
	}
	if (atexit(myexit2) != 0) {
		perror("atexit");
		exit(1);
	}

	printf("main thread is done\n");
}	
