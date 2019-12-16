#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "fifo.h"

/*
	This program charge of server rule.
	It make fifo file to get request from client.
	And wait untill request is come.
	if client request to server, server reply to client's fifo file.
	and back to wait untill request is come.
	if signal that SIGINT is come, server program remove it's fifo file before terminate program.
*/


// when SIGINT come, remove server fifo file.
// and terminate process.
void SigIntHandler(int signo) {
	if (remove(SERV_FIFO) < 0) {
		perror("remove");
		exit(1);
	}
	exit(0);
}


void main() {
	int fd, cfd, n;
	MsgType msg;
	// register SIGINT handler.
	if(signal(SIGINT, SigIntHandler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	// make server fifo file.
	if(mkfifo(SERV_FIFO, 0600) < 0) {
		// if .fifo file already exist, then print error and exit process.
		if(errno != EEXIST) {
			perror("mkfifo");
			exit(1);
		}
	}
	
	// open server fifo file.
	if((fd = open(SERV_FIFO, O_RDWR)) < 0){
		perror("open");
		exit(1);
	}

	while(1){

		// wait when client request to server fifo file.
		if((n = read(fd, (char *)&msg, sizeof(msg))) < 0) {
			// when externel interrupt occur, then ignore this signal. 
			if (errno == EINTR) {
				continue;
			}
			else {
				perror("read");
				exit(1);
			}
		}

		printf("Received request: %s.......", msg.data);

		// open client fifo file for reply to client.
		if((cfd = open(msg.returnFifo, O_WRONLY)) < 0) {
			perror("open");
			exit(1);
		}
		
		//send message to client.
		sprintf(msg.data, "This is a reply from %d.", getpid());
		write(cfd, (char *)&msg, sizeof(msg));
		
		// disconnect client.
		close(cfd);
		printf("Replied.\n");
	}
}
