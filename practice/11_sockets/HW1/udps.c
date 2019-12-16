#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include "udp.h"
/*
	This program make udp server.
    Udp server make socket and bind ip(anywhere) and port number.
	And this server can get request and send reply to client.
*/
int Sockfd;

void CloseServer() {
	close(Sockfd);
	printf("\nUDP Server exit.....\n");
	exit(0);
}

void main() {
	int cliAddrLen;
	struct sockaddr_in cliAddr, servAddr;
	MsgType msg;

	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind");
		exit(1);
	}

	printf("UDP Server started....\n");

	cliAddrLen = sizeof(cliAddr);
	while (1) {
		if (recvfrom(Sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&cliAddr, &cliAddrLen) < 0) {
			perror("receivfrom");
			exit(1);
		}

		printf("Received request: %s.....\n", msg.data);
		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is reply from %d", getpid());
		if (sendto(Sockfd, (char *)&msg, sizeof(msg),0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0) {
			perror("sendto");
			exit(1);
		}
		printf("Replied.\n");
	}
}
