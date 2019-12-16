#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "tcp.h"

/*
	This program make tcp client.
    Tcp client make socket and try to connection server.
	If connection success, it can sent and receive by writing and reading using socket.
*/
void main() {
	int sockfd;
	struct sockaddr_in servAddr;
	MsgType msg;

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect");
		exit(1);
	}

	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
	if (write(sockfd, (char *)&msg, sizeof(msg)) < 0) {
		perror("write");
		exit(1);
	}
	printf("Sent a request......");
	
	if (read(sockfd, (char *)&msg, sizeof(msg)) < 0) {
		perror("read");
		exit(1);
	}

	printf("Received reply: %s\n", msg.data);
	close(sockfd);
}
