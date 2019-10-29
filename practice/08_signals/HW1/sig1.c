/*
This program pause utill getting signal.
And then this program print Terminate and terminate.
*/
 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigIntHandler(int sigNo){
	printf("Terminate this process\n");
	exit(0);
}

void main() {

	signal(SIGINT, sigIntHandler);
	printf("If you put down ctrl + C, this process shut down\n");
	while(1)
		pause();

}
