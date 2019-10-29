/*
This program solve racing problem by using wait system call. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void CharAtaTime(char *str) {
	char *ptr;
	int c,i;
	for (ptr = str; c = *ptr++; ) {
		for (i = 0; i <999999;i++)
			;
		putc(c,stdout);
	}
}

void main() {
	pid_t pid;
	int status;

	if((pid = fork()) < 0 ) {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		CharAtaTime("output from child\n");
	else {
		wait(&status);
		CharAtaTime("output from parent\n");
	}
}
