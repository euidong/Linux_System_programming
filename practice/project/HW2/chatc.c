#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <pthread.h>
#include "chat.h"
#define MAX_BUF 256

int Sockfd;
pthread_t Tid;

// send Thread.
void *sendMessage(void *dummy) {
	char buffer[MAX_BUF];
    while(1) {
        fgets(buffer, MAX_BUF, stdin);
        if (send(Sockfd, buffer, strlen(buffer) + 1, 0)< 0) {
            perror("send");
            pthread_exit(NULL);
        }
    }
}

// chat client.
// get ID from user and send User ID.
// start chatting and continued when press ^C.
// recv control in this thread.(main)
// send controled by other thread. 
void ChatClient(void) {
	char buf[MAX_BUF];
	int count, n;
	fd_set fdset;

	printf("Enter ID: ");
	fflush(stdout);
	// get stdout 
	fgets(buf, MAX_BUF, stdin);
	*strchr(buf, '\n') = '\0';
	if (send(Sockfd, buf, strlen(buf)+1, 0) < 0) {
		perror("send");
		exit(1);
	}
	printf("Press ^C to exit\n");

	if (pthread_create(&Tid, NULL, (void *)sendMessage, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
		
    while(1) {
        if ((n = recv(Sockfd, (void *)&buf, MAX_BUF, 0)) < 0) {
            perror("recv");
            pthread_exit(NULL);
        }

        //The value 0 indicates the connection is closed.
        if (n==0) {
            fprintf(stderr, "Server terminated.....\n");
            pthread_cancel(Tid);
			close(Sockfd);
            exit(0);
        }
        printf(">%s\n", buf);
    }
}

// close client socket and cancel pthread.
void CloseClient(int signo) {
	// close socket.
	close(Sockfd);
	printf("\nChat client terminated.....\n");

	pthread_cancel(Tid);
	exit(0);
}

void main(int argc, char *argv[]) {
	struct sockaddr_in servAddr;
	struct hostent *hp;

	// must enter domain or ip address 
	if (argc != 2) {
		fprintf(stderr, "Usage: %s ServerIPaddress\n", argv[0]);
		exit(1);
	}
	
	// declare socket as ip4 and tcp.
	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	
	// set ip address and port.
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(SERV_TCP_PORT);

	// translate string ip address to integer form.
	if (isdigit(argv[1][0])) {
		servAddr.sin_addr.s_addr = htonl(inet_addr(argv[1]));
	}
	
	// translate DNS ip address to integer form.
	else {
		if ((hp = gethostbyname(argv[1])) == NULL) {
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		// copy hp address to servAddr.
		memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
	}
	
	// request connection to server.
	if (connect(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect");
		exit(1);
	}

	// register signal ^C
	signal(SIGINT, CloseClient);
	
	// call chating program.
	ChatClient();
}
