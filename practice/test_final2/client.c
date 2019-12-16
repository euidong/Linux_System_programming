#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
#include <string.h>
#include "game.h"

int Sockfd;

struct sockaddr_in ServAddr;


void main(int argc, char *argv[]) {
	
	struct hostent *hp;

	MsgType msg;
	
	int myID;
	char cmd[MAX_BUF];
	int ServAddrLen = sizeof(ServAddr);
	// 0. check argc
	if (argc != 3) {
		fprintf(stderr, "Usage: %s DNS username\n", argv[0]);
		exit(1);
	}
	
	// 1. make socket
	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	
	ServAddr.sin_family = PF_INET;
	ServAddr.sin_port = SERV_PORT;

	if (isdigit(argv[1][0])) {
		ServAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else {
		if ((hp = gethostbyname(argv[1])) == NULL) {
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		memcpy(&ServAddr.sin_addr, hp->h_addr, hp->h_length);
	}

	// 2. sent message(logIn)
	msg.id = -1;
	sprintf(msg.cmd,"%s", argv[2]);
	
	if (sendto(Sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0) {
		perror("sendto");
		exit(1);
	}

	// 3. get UserID
	if (recvfrom(Sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&ServAddr, &ServAddrLen) < 0) {
		perror("recvfrom");
		exit(1);
	}

	myID = msg.id;

	while(1) {
	// 4. listen shell input
		printf("Key> ");
		fflush(stdout);

		fgets(cmd, sizeof(cmd), stdin);

	// 5. send message to server 
		if (cmd[0] == '0') {
			sprintf(msg.cmd,"%s", argv[2]);
			msg.id = myID;
			if (sendto(Sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&ServAddr, ServAddrLen) < 0) {
				perror("sendto");
				exit(1);
			}
			exit(0);
		}
		else {
			sprintf(msg.cmd, "%s", cmd);
			if (sendto(Sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&ServAddr, ServAddrLen) < 0) {
				perror("sendto");
				exit(1);
			}
		}
	}

}
