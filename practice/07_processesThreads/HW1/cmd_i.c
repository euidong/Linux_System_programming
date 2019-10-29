/*
This program express command processing and waiting by using iteration.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_CMD 256

// sleep 1 time.
void DoCmd(char *cmd) {
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
}


void main() {
	char cmd[MAX_CMD];

	while (1) {
		printf("CMD> ");
		//get line
		fgets(cmd, MAX_CMD, stdin);
		if (cmd[0] == 'q')
			break;
		//process cmd
		DoCmd(cmd);
	}
}

