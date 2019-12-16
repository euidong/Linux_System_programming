#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "fifo.h"


/*
   This program charge of client.
   It make fifo file can get server's reply that name is ".fifo" + process ID.
   And it open server fifo file and sent message with fifo file that client made.
   When server reply that, client get message and remove it's fifo file.
*/
void main(){
	char fname[MAX_FIFO_NAME];
	int fd, sfd, n;
	MsgType msg;
	
	//make fifo file for get reply from server
	sprintf(fname, ".fifo%d", getpid());
	if (mkfifo(fname, 0600) < 0) {
		perror("mkfifo");
		exit(1);
	}
	
	// open it's fifo file.
	if ((fd = open(fname, O_RDWR)) < 0) {
		perror("open");
		exit(1);
	}
	
	// open server's fifo file.
	if ((sfd = open(SERV_FIFO, O_RDWR)) < 0) {
		perror("open");
		exit(1);
	}

	// make message to sent server with return file name.
	strcpy(msg.returnFifo, fname);
	sprintf(msg.data, "This is a request from %d.", getpid());

	// sent message.
	write(sfd, (char *)&msg, sizeof(msg));
	printf("Sent a request........");
	
	// wait when reply come
	if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0) {
		perror("read");
		exit(1);
	}

	printf("Received reply: %s\n", msg.data);

	close(fd);
	close(sfd);
	
	// remove it's fifo file.
	if(remove(fname) < 0) {
		perror("remove");
		exit(1);
	}
}

