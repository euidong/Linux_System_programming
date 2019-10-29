/*
This program make sleep function using alarm system call.
alarm is counting time.
*/

//this function noting to do.
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigAlarmHandler(int sigNo) {
	return;
}

unsigned int mysleep(unsigned int sec) {
	if (signal(SIGALRM, sigAlarmHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}
	alarm(5);

	pause();
	
	return alarm(0);
}

void main() {
	printf("Wait for 5 Seconds....\n");
	
	mysleep(5);
}
