#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include "tcp.h"
#include <string.h>

int Sockfd;

void SigIntHandler(int sigNo) {
	close(Sockfd);
	exit(0);
}

void main() {
	signal(SIGINT, SigIntHandler);
	int n, i;
	int fd;
	char buf[MAX_BUF];

	int cliAddrLen, newSockfd;
	struct sockaddr_in servAddr, cliAddr;
	
	pid_t pid;

	struct timeval enterTime;

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) <0) {
		perror("exit");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = SERV_PORT;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5);

	while(1) {
		newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
		if (newSockfd < 0) {
			perror("accept");
			exit(1);
		}


		if ((pid=fork()) < 0) {
			perror("fork");
			exit(1);
		}

		// childprocess
		else if (pid == 0) {
			if (( n = read(newSockfd, buf, sizeof(buf))) < 0) {
				perror("recv");
				exit(1);
			}
			else if (n > 0) {
				if ((fd = open(buf, O_RDWR | O_APPEND | O_CREAT)) < 0) {
					perror("open");
					exit(1);
				}
				chmod(buf, 0660);
					
				gettimeofday(&enterTime, NULL);
				sprintf(buf, "%d", (int)enterTime.tv_usec);
				write(fd, buf, sizeof(enterTime.tv_usec));
				write(fd, "\n", 1);
				close(fd);
			}
			exit(0);
		}
		close(newSockfd);
	}
}


