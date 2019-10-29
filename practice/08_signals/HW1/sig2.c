/*
This program setting 2 signal handling one function.
if signal is SIGUSR1, print Received message.
if signal is SIGUSR2, print Received message, too.
the other signal will terminate this process.

We can check this order.
1. other terminal : command "ps -ef | grep lsp41"
2. catch ./sig2's processID.
3. kill -USR1 processID
4. kill -USR2 processID
5. kill -9 processID
*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void SignHandler(int sigNo) {
	if (sigNo == SIGUSR1) {
		printf("Received a SIGUSR1 signal\n");
	}

	else if (sigNo == SIGUSR2) {
		printf("Received a SIGUSR2 signal\n");
	}

	else {
		printf("Received unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}

void main() {
	if(signal(SIGUSR1, SignHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}
	if(signal(SIGUSR2, SignHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}
	for ( ; ; )
		pause();
}
