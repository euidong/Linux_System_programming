/*
This program shows different from two process's action.
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// declare global variable
int Var = 6;
char Buf[] = "a write to stdout\n";

void main() {
	// declare local variable
	int var;
	pid_t pid;

	var = 88;
	write(STDOUT_FILENO, Buf, sizeof(Buf) -1);
	printf("Before fork\n");

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	//change variable in child process.
	else if (pid == 0) {
		Var++;
		var++;
	}
	//sleep parent process.
	else {
		sleep(2);
	}

	//child print 7 89
	//parent print 6 88
	printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
}
