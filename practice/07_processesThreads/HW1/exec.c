/*
   This program test exec 3ways.
   First is execl,
   Second is execv
   Last is execlp
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void main() {
	pid_t pid;
	char *argv[] = {"mycp2", "exec.c", "exec2.c", NULL};

	//First is execl
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	//path include execution file name.
	else if (pid == 0) {
		if(execl("/home/lsp41/07_processesThreads/HW1/mycp2", "mycp2", "exec.c", "exec1.c", NULL) < 0) {
			perror("execl");
			exit(1);
		}
		exit(0);
	}
	
	//wait when child process is done.
	if (waitpid(pid, NULL, 0) < 0) {
		perror("waitpid");
		exit(1);
	}
		
	//Second is execv
	if ((pid = fork()) < 0 ) {
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
		if (execv("/home/lsp41/07_processesThreads/HW1/mycp2", argv) < 0) {
			perror("execv");
			exit(1);
		}
		exit(0);
	}
	if (waitpid(pid,NULL,0) < 0) { 
		perror("waitpid");
		exit(1);
	}

	//Last is execlp
	if((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
		if(execlp("env", "env", NULL) < 0) {
			perror("execlp");
			exit(1);
		}
		exit(0);
	}
	if (waitpid(pid,NULL,0) < 0) {
		perror("waitpid");
		exit(1);
	}
}		

