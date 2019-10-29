/*
This program make bash by using process forking.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD 256

void DoCmd(char *cmd) {
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
}

void main() {
	char cmd[MAX_CMD];
	pid_t pid;
	while(1) {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);
		if (cmd[0] == 'q')
			break;
		if ((pid = fork()) < 0 ) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			DoCmd(cmd);
			exit(0);
		}
		else {
			//wait response from child process.
			wait(NULL);
		}
	}
}
