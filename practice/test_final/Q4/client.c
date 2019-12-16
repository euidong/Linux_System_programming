#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"
#include <netdb.h>
#include <string.h>
#include <ctype.h>

void main(int argc, char *argv[]) {
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s serverAddress userName\n", argv[0]);
		exit(1);
	}

	int sockfd;
	struct sockaddr_in servAddr;
	struct hostent *hp;
	
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = SERV_PORT;
	
	if (isdigit(argv[1][0])) {
		servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else {
		if ((hp = gethostbyname(argv[1])) == NULL) {
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
	}

	if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) <0) {
		perror("connect");
		exit(1);
	}

	if (write(sockfd, argv[2], sizeof(argv[2])) < 0) {
		perror("write");
		exit(1);
	}

	close(sockfd);
}
