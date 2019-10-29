/*
This program execution periodic task, every 1 sec print one dot.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
unsigned int ALARM_SEC;

void SigAlarmHandler(int sigNo) {
	//don't have to assign signal every time.
	/*
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}	
	*/
	
	printf(".");
	fflush(stdout);
	alarm(ALARM_SEC);
}


int SetPeriodicAlarm(unsigned int nsec) {
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}
	ALARM_SEC = nsec;
	alarm(nsec);
}


void main() {
	printf("Doing something every one seconds");

	SetPeriodicAlarm(1);

	for( ; ; )
		pause();
}
