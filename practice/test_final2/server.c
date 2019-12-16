#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "game.h"


#define MAX_CLIENT 5

typedef struct {
	int inUse;
	pthread_t tid;
	struct sockaddr_in cliAddr;
} ClientType;

struct sockaddr_in CliAddr;

int Sockfd;
sem_t Mutex;

ClientType Client[MAX_CLIENT];

int GetID() {
	int i;
	for (i = 0; i <MAX_CLIENT; i++) {
		if(!Client[i].inUse) {
			Client[i].inUse = 1;
			return i;
		}
	}
}

// processing thread.
void *GetClientsCMD(void *dummy) {
	MsgType msg = *(MsgType *)dummy;
	if (sem_wait(&Mutex) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}

	// not logIn
	if (msg.id == -1) {
		int id = GetID();
		Client[id].cliAddr = CliAddr;
		printf("%s login (UID=%d)\n", msg.cmd, id);
		MsgType buf;
		buf.id = id;
		if (sendto(Sockfd, (char *)&buf, sizeof(buf),0, (struct sockaddr *)&CliAddr, sizeof(CliAddr)) <0)	{
			perror("sendto");
			pthread_exit(NULL);
		}
	}
	
	// completed logIn
	else {
		if (msg.cmd[0] != '1' && msg.cmd[0] != '2' && msg.cmd[0] != '3' && msg.cmd[0] != '4') {
			Client[msg.id].inUse = 0;
			printf("%s logout (UID=%d)\n", msg.cmd, msg.id);
		}
		else 
			printf("%d/%s", msg.id, msg.cmd);
	}

	if (sem_post(&Mutex) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}
}

//signal 
void SigIntHandler(int sigNo) {
	close(Sockfd);
	sem_destroy(&Mutex);
	exit(0);
}

void main() {
	signal(SIGINT, SigIntHandler);
	struct sockaddr_in servAddr;
	int n;
	MsgType msg;
	pthread_t tid;
	
	if (sem_init(&Mutex, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}

	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
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

	int CliAddrLen = sizeof(CliAddr);
	while(1) {
		// catch all signal
		if ((n = recvfrom(Sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&CliAddr, &CliAddrLen)) < 0) {
			perror("recvfrom");
			exit(1);
		}
		
		// client message handler
		else {
			if (pthread_create(&tid, NULL, (void *)GetClientsCMD, (void *)&msg) < 0) {
				perror("pthread_creat");
				exit(1);
			}
		}
	}

}
