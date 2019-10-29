/*
This program test wait system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

// This handler handle SIGCHLD.
// If SIGCHLD come then print and exit.
void SigChldHandler(int sigNo) {
	printf("A child killed.....\n");
	exit(0);
}

void main() {
	pid_t pid;
	int status;

	// assign signal handler.
	signal(SIGCHLD,SigChldHandler);

	if ((pid=fork()) < 0){
		perror("fork");
		exit(1);
	}

	else if (pid == 0) {
		/*child*/
		printf("I'm a child\n");
		sleep(2);
		exit(0);
	}
	else {
		/*parent*/
		// doing asynchronocing utill child is done.
		while(1)
			;
	}
}
