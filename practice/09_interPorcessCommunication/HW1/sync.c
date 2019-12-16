#include <stdio.h>
#include <stdlib.h>
#include "synclib.h"

#define NLOOPS 5

/*
	This program make 2 pipe and communication with this.
	One is used to send data from chid to parent. The other is reversation.
*/
void main(){
	int i;
	pid_t pid;
	
	// make two pipe.
	TELL_WAIT();

	// make process.
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	// child 
	else if (pid == 0) {
		// child do tell and wait to read, 5 times.
		for (i = 0 ; i < NLOOPS; i++) {
			// child tell to parent.
			TELL_CHILD();
			printf("Child : Tell to parent\n");
			printf("Child : Wait for parent to tell\n");
			// child wait untill parent sent.
			WAIT_CHILD();
		}
	}
	// parent 
	else {
		// parent do wait to read and tell, 5 times.
		for (i = 0 ; i < NLOOPS; i++) {
			printf("Parent : Wait for parent to tell\n");
			// parent wait untill child sent.
			WAIT_PARENT();
			// parent sent to child.
			TELL_PARENT();
			printf("Parent : Tell to parent\n");
		}
	}
}
