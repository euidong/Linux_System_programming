#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "tcp.h"

int Sockfd, NewSockfd;
struct sockaddr_in ServAddr, CliAddr;

void SigIntHandler(int sigNo) {
	close(Sockfd);
	close(NewSockfd);
	exit(0);
}

void main() {
	signal(SIGINT, SigIntHandler);
	int cliAddrLen = sizeof(CliAddr);
	char buf[MAX_BUF];
	int n;
	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    	perror("socket");
    	exit(1);
	}
	bzero((char *)&ServAddr, sizeof(ServAddr));
	ServAddr.sin_family = PF_INET;
	ServAddr.sin_port = htons(SERV_PORT);
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(Sockfd, (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0) {
    	perror("bind");
    	exit(1);
	}
	listen(Sockfd, 5);
	NewSockfd = accept(Sockfd, (struct sockaddr *)&CliAddr, &cliAddrLen);
	if (NewSockfd < 0) {
    	perror("accept");
    	exit(1);
	}
	if ((n =read(NewSockfd, buf, MAX_BUF)) < 0) {
    	perror("read");
    	exit(1);
	}
	printf("%s\n", buf);
	sprintf(buf, "hi");
	if (write(NewSockfd, buf, MAX_BUF) < 0) {
    	perror("write");
    	exit(1);
	}
	if (close(NewSockfd) < 0) {
    	perror("close");
    	exit(1);
	}
	if (close(Sockfd) < 0) {
    	perror("close");
    	exit(1);
	}
}	
