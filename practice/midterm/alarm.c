#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#define MAX_BUF 256

static char message[MAX_BUF];

void SigAlrmHandler(int sigNo){
	system(message);
	exit(0);
}


void main(int argc, char *argv[]) {
	
	if(argc < 3){
		printf("Usage: %s time message", argv[0]);
		exit(1);
	}
	strcpy(message, "banner");
	int i;
	for (i = 2; argv[i] != NULL; i++)
	{	
		strcat(message, " ");
		strcat(message, argv[i]);
	}
	signal(SIGALRM, SigAlrmHandler);
	alarm(atoi(argv[1]));

	pause();
}
