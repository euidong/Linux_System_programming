#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
/*
This program fork 1 process and independently execute. 
*/

void main()
{
	int		pid;

	//fork process. 
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		/* child */
		printf("I am %d. My parent is %d.\n", getpid(), getppid());
	}
	else  {
		/* parent */
		printf("I am %d. My child is %d.\n", getpid(), pid);
	}
}
