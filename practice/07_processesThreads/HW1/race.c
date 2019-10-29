/*
This program show racing between parent process and child process.
They race to get same resource which is shell. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void CharAtaTime(char *str) {
	char *ptr;
	int c,i;

	//Select where to put.
	setbuf(stdout,NULL);
	for (ptr = str; c = *ptr++; ) {
		for (i = 0 ; i < 999999; i++)
			;
		putc(c,stdout);
	}
}

void main() {
	pid_t pid;
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	//They race to get resource.
	else if (pid == 0)
		CharAtaTime("output from child\n");
	else 
		CharAtaTime("output from parent\n");
}
