/*
This program make bash by using thread.

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD 256

void DoCmd(char *cmd) {
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");

	pthread_exit(NULL);
}

void main() {
	char cmd[MAX_CMD];

	pthread_t tid;

	while(1) {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);
		if (cmd[0] == 'q')
			break;
		if (pthread_create(&tid, NULL, (void*)DoCmd,(void*)cmd) < 0) {
			perror("pthread_create");
			exit(1);
		}

		pthread_join(tid, NULL);
	}
}
