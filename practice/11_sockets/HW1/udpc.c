#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "udp.h"

/*
	This program make udp client.
    It make socket and directly send request to server using sendto.
	And can get reply using recvfrom.
*/

void main(){
	int sockfd, sockLen;
	struct sockaddr_in sockAddr;
	MsgType msg;

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) <0) {
		perror("socket");
		exit(1);
	}
	bzero((char *)&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	sockAddr.sin_port = htons(SERV_UDP_PORT);
	sockLen = sizeof(sockAddr);
	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is request from %d\n", getpid());

	if (sendto(sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&sockAddr, sockLen) < 0) {
		perror("sendto");
		exit(1);
	}
	printf("Sent a request");
	if (recvfrom(sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&sockAddr, &sockLen) < 0) {
		perror("recvform");
		exit(1);
	}
	printf("Replyed: %s\n", msg.data);
}
