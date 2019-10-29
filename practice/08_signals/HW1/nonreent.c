/*
This program test signal's incompletion.
It's re-entrant is incomplete.

So, It can interrupt processing.
we must not depend on signal.
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

void MyAlarmHandler(int sigNo) {
	struct passwd *rootptr;

	signal(SIGALRM, MyAlarmHandler);

	alarm(1);

	printf("in signal Handler\n");

	// how can change main's ptr??
	if ((rootptr = getpwnam("root")) == NULL) {
			perror("getpwnam");
			exit(1);
	}

	return;
}

void main(){
	struct passwd *ptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);
	
	for ( ; ; ) {
		if ((ptr = getpwnam("lsp41")) == NULL) {
			perror("getpwnam");
			exit(1);
		}

		if(strcmp(ptr->pw_name, "lsp41") != 0) {
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
