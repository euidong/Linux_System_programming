#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "udp.h"


int Sockfd;
struct sockaddr_in ServAddr, CliAddr;

void SigIntHandler(int sigNo) {
	close(Sockfd);
	exit(1);
}

void main() {
	signal(SIGINT, SigIntHandler);
	int servAddrLen = sizeof(ServAddr);
	int cliAddrLen = sizeof(CliAddr);
	char buf[MAX_BUF];
	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    	perror("socket");
    	exit(1);
	}
	bzero((char *)&ServAddr, servAddrLen);
	ServAddr.sin_family = PF_INET;
	ServAddr.sin_port = htons(SERV_PORT);
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(Sockfd, (struct sockaddr *)&ServAddr, servAddrLen) < 0) {
    	perror("bind");
    	exit(1);
	}
	if (recvfrom(Sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&CliAddr, &cliAddrLen) <0) {
   		perror("recvfrom");
   		exit(1);
	}
	printf("%s\n", buf);
	sprintf(buf, "hi");
	if (sendto(Sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&CliAddr, cliAddrLen) < 0) {
    	perror("sendto");
    	exit(1);
	}
}
