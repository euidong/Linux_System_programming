#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Pfd1 : child -> parent
// Pfd2 : parent -> child
static int Pfd1[2], Pfd2[2];


// make two pipe.
void TELL_WAIT(void){
	if(pipe(Pfd1) < 0 ||pipe(Pfd2) < 0) {
		perror("pipe");
		exit(1);
	}
}

// parent tell child using pfd2.
void TELL_PARENT(void) {
	if(write(Pfd2[1], "c", 1) != 1) {
		perror("write");
		exit(1);
	}	
}

// parent wait untill child sent using pfd1.
void WAIT_PARENT(void) {
	char c;
	if(read(Pfd1[0], &c, 1) != 1) {
		perror("read");
		exit(1);
	}

	// flag is 'p'
	if (c != 'p') {
		fprintf(stderr,"WAIT_PARENT: Incorrect data");
		exit(1);
	}
}

// child tell parent using pfd1.
void TELL_CHILD(void) {
	// tell 'p'
	if(write(Pfd1[1], "p", 1) != 1) {
		perror("write");
		exit(1);
	}
}

// child wait untill parent sent using pfd2.
void WAIT_CHILD(void) {
	char c;

	if (read(Pfd2[0], &c, 1) != 1) {
		perror("read");
		exit(1);
	}
	// if read 'c' , it is error.
	if (c != 'c') {
		fprintf(stderr,"WAIT_CHILD: incorrect data");
		exit(1);
	}
}
