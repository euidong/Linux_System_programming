/*
This program test wait system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
	pid_t pid;
	int status;

	if ((pid=fork()) < 0){
		perror("fork");
		exit(1);
	}

	else if (pid == 0) {
		/*child*/
		printf("I'm a child\n");
		sleep(2);
	}
	else {
		/*parent*/
		// wait untill child is done.
		wait(&status);
		printf("A child killed with %d status\n", status);
	}
}
