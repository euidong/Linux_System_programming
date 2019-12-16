#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "msg.h"

// Messege queue mode is read and write.
#define MSG_MODE (0600)

void main() {
	int msqid, n;
	MsgType msg;
		
	// get message queue made by msgq1.
	if ((msqid = msgget(MSG_KEY, MSG_MODE)) < 0) {
		perror("msgget");
		exit(1);
	}

	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
   	
	// send message to msgq1
	if ((n = msgsnd(msqid, (char *)&msg, sizeof(msg), 0)) < 0) {
		perror("msgsnd");
		exit(1);
	}

	printf("Sent a request....");

	// get message from msgq1.
	if ((n = msgrcv(msqid, (char *)&msg, sizeof(msg), MSG_REPLY, 0)) < 0) {
		perror("msgrcv");
		exit(1);
	}
	printf("Received Reply: %s\n", msg.data);

}
