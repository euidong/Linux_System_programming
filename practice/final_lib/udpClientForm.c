#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include "udp.h"

int Sockfd;
struct sockaddr_in ServAddr, CliAddr;

void main(int argc, char *argv[]) {
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s detination\n", argv[0]);
		exit(1);
	}

	int servAddrLen = sizeof(ServAddr);
	int cliAddrLen = sizeof(CliAddr);
	char buf[MAX_BUF];
	struct hostent *hp;

	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    	perror("socket");
    	exit(1);
	}

	bzero((char *)&ServAddr, servAddrLen);
	ServAddr.sin_family = PF_INET;
	ServAddr.sin_port = htons(SERV_PORT);
	
	if (isdigit(argv[1][0])) {
		ServAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else {
		if (!(hp = gethostbyname(argv[1]))) {
			fprintf(stderr, "Unknown host %s\n", argv[1]);
		}
		memcpy(&ServAddr.sin_addr, hp->h_addr, hp->h_length);
	}
	sprintf(buf, "hello");
	if (sendto(Sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&ServAddr, servAddrLen) <0) {
   		perror("recvfrom");
   		exit(1);
	}

	if (recvfrom(Sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&ServAddr, &servAddrLen) < 0) {
    	perror("sendto");
    	exit(1);
	}
	printf("%s\n", buf);
}
