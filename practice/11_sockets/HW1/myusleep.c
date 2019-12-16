#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
/*
	This program make sleep system call by using select function.
    Select combine two file descriptor.
	One is tv_sec , the other is tv_usec.
	So, can make function 2 input.
	One is second, the other is milli second.	
*/
void myusleep(int secs, int usecs) {
	struct timeval tm;

	tm.tv_sec = secs;
	tm.tv_usec = usecs;

	if (select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &tm) < 0) {
		perror("select");
		return;
	}
}

void main() {
	printf("Sleep for 1.5 seconds.....\n");
	myusleep(1, 500000);
}

