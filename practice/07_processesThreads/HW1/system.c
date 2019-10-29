/*
This program use system. 
This system call requests execution command. 
So, this doesn't need to fork, wait.
*/
#include <stdio.h>
#include <stdlib.h>

void main() {
	int status;

	// request date command 
	if ((status = system("date")) < 0) {
		perror("system");
		exit(1);
	}

	printf("exit status = %d\n", status);
	
	// wrong input
	if ((status = system("nosuchcommand")) < 0) {
		perror("system");
		exit(1);
	}

	printf("exit status = %d\n", status);
	
	// request who command
	// exit 	
	if ((status = system("who; exit 44")) < 0 ) {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);
}
