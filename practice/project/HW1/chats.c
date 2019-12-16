#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <sys/un.h>
#include <pthread.h>
#include "chat.h"

#define DEBUG

#define MAX_CLIENT 5
#define MAX_ID 32
#define MAX_BUF 256

/*
	This program change state from using multithread to multiplexing.
*/

// ClientType structure
typedef struct {
	int firstConnect; // checking connection Time.
	int sockfd; // socket fd
	int inUse; // check Use or not
	char uid[MAX_ID]; // user ID
} ClientType;

int Sockfd;
pthread_mutex_t Mutex;

// MAX Client is 5.
ClientType Client[MAX_CLIENT];

// empty client get
int GetID() {
	int i;
	for (i = 0; i < MAX_CLIENT; i++) {
		if (!Client[i].inUse) {
			Client[i].inUse = 1;
			return i;
		}
	}
}

// Broad casting to other client.
void SendToOtherClients(int id, char *buf) {
	int i;
	char msg[MAX_BUF+MAX_ID];

	sprintf(msg, "%s> %s", Client[id].uid, buf);
#ifdef DEBUG
	printf("%s", msg);
	fflush(stdout);
#endif
	pthread_mutex_lock(&Mutex);
	for (i=0; i < MAX_CLIENT; i++) {
		if (Client[i].inUse && (i != id)) {
			if (send(Client[i].sockfd, msg, strlen(msg)+1, 0) < 0) {
				perror("send");
				exit(1);
			}
		}
	}
	pthread_mutex_unlock(&Mutex);
}


// when signal come, close server
// close socket(server and client)
// destroy mutex
void CloseServer(int signo) {
	int i;
	close(Sockfd);

	for (i = 0 ; i < MAX_CLIENT; i++) {
		if (Client[i].inUse) {
			close(Client[i].sockfd);
		}
	}
	if (pthread_mutex_destroy(&Mutex) < 0) {
		perror("pthread_mutex_destroy");
		exit(1);
	}
	printf("\nChat server terminated....\n");
	exit(0);
}

// Server setting
// First, create and set socket to get acception request from client.
// Second, set FD_SET to get all request without thread.
// Third, all request managed by fd_set. (Can check FD_ISSET)
void main(){
	int newSockfd, cliAddrLen, id, i, count, n,one = 1;
	struct sockaddr_in cliAddr, servAddr;
	fd_set fdvar;
	for (i = 0; i< MAX_CLIENT; i++) {
		Client[i].firstConnect = 1;
	}

	signal(SIGINT, CloseServer);

	if (pthread_mutex_init(&Mutex, NULL) < 0) {
		perror("pthread_mutex_init");
		exit(1);
	}

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	if (setsockopt(Sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
		perror("setsockopt");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5);

	printf("Chat server started.....\n");

	cliAddrLen = sizeof(cliAddr);
	while(1) {
		FD_ZERO(&fdvar);
		FD_SET(Sockfd, &fdvar);
		for (i =0; i < MAX_CLIENT; i++) {
			FD_SET(Client[i].sockfd, &fdvar);
		}
		if ((count = select(10, &fdvar, (fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL)) < 0) {
			perror("select");
			exit(1);
		}
		while(count--) {
			if (FD_ISSET(Sockfd, &fdvar)) {
				newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
				if (newSockfd < 0) {
					perror("accept");
					exit(1);
				}
				id = GetID();
				Client[id].sockfd = newSockfd;
			}
			else {
				for (i = 0; i < MAX_CLIENT; i++) {
					if (FD_ISSET(Client[i].sockfd, &fdvar)) {
						char buffer[MAX_BUF];
						if (Client[i].firstConnect) {
							if ((n = recv(Client[i].sockfd, Client[i].uid, MAX_ID, 0)) < 0) {
								perror("recv");
								exit(1);
							}
							else if (n > 0) {
								printf("Client %d log-in(ID: %s)....\n", i, Client[i].uid);
								SendToOtherClients(i, Client[i].uid);
								Client[i].firstConnect = 0;
							}
							else {
								pthread_mutex_lock(&Mutex);
								close(Client[i].sockfd);
								Client[i].inUse = 0;
								pthread_mutex_unlock(&Mutex);
							}
						}
						else {
							if ((n = recv(Client[i].sockfd, buffer, MAX_BUF, 0)) < 0) {
								perror("recv");
								exit(1);
							}
							else if (n == 0) {
								printf("Client %d log-out(ID: %s)....\n", i, Client[i].uid);
                                pthread_mutex_lock(&Mutex);
                                close(Client[i].sockfd);
                                Client[i].sockfd = -1;
								Client[i].inUse = 0;
								Client[i].firstConnect = 1;
                                pthread_mutex_unlock(&Mutex);
								
                                strcpy(buffer, "log-out....\n");
                                SendToOtherClients(i, buffer);
							}
							else {
								SendToOtherClients(i, buffer);
							}
						}
					}
				}
			}
		}
	}
}

