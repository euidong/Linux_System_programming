#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include "msg.h"

// message mode read write and IPC create.
#define MSG_MODE (0600 | IPC_CREAT)


/*
	This program make message queue.
    And give and take message with requester.	
*/

void main() {
	int msqid, n;
	MsgType msg;

	// make message queue.
	if ((msqid = msgget(MSG_KEY, MSG_MODE)) < 0) {
		perror("msgget");
		exit(1);
	}

	// get receive request from message queue.
	if ((n = msgrcv(msqid, (char*)&msg, sizeof(msg), 0, 0)) < 0) {
		perror("msgrcv");
		exit(1);
	}

	printf("Received request: %s.......", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());

	// sent message to requester.
	if (msgsnd(msqid, (char *)&msg, sizeof(msg), 0) < 0) {
		perror("msgsnd");
		exit(1);
	}

	printf("Replied. \n");
	sleep(1);
	
	// exit message queue.
	if(msgctl(msqid, IPC_RMID, 0) < 0) {
		perror("msgctl");
		exit(1);
	}
}
