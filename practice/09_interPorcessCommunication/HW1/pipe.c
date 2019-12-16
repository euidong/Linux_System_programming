#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 128

/*
This program make pipe and inter communication by using pipe.
*/

void main(){
	int n, fd[2], fd2[2];
	pid_t pid;
	char buf[MAX_BUF];

	// make pipe to kernel.
	// pipe fd ( parent => child )
	// pipe fd2( child => parent )
	if (pipe(fd) < 0 || pipe(fd2) < 0) {
		perror("pipe");
		exit(1);
	}
	
	// make process
	if ((pid = fork()) <0){
		perror("fork");
		exit(1);
	}
	
	//child process 
	else if(pid == 0) {
		// close output pipe.
		close(fd[1]);
		
		// close input pipe.
		close(fd2[0]);
		printf("Child : Wait for parent to send data\n");
		
		// wait untill data come to fd pipe.
		if ((n = read(fd[0], buf, MAX_BUF)) < 0) {
			perror("read");
			exit(1);
		}

		// print receive data.
		printf("Child : Received data from parent : ");
		fflush(stdout);
		write(1, buf, n);
	

		// write to parent using fd2 pipe.
		strcpy(buf, "Nice to meet you\n");
		printf("Child : Send data to parent\n");
		write(fd2[1], buf, strlen(buf) +1);
	}
	else {
		// close input pipe.
		close(fd[0]);
		close(fd2[1]);
		strcpy(buf, "Hello, world!\n");
		printf("Parent: Send data to child\n");
		
		// send to fd pipe "Hello, world!\n"
		write(fd[1], buf, strlen(buf)+1);


		// wait receive from child.
		printf("Parent : Wait for child to send data\n");
		if ((n =read(fd2[0], buf, MAX_BUF)) < 0) {
			perror("read");
			exit(1);
		}
		
		// print data from child.
		printf("Parent : Received data from child : ");
		fflush(stdout);
		write(STDOUT_FILENO, buf, n);
	}
	exit(0);
}
