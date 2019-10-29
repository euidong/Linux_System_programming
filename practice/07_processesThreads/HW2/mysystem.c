#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMD 256
#define MAX_LENGTH 256

/*
This program make system that is system call.
First, string parsing.
Second, fork.
Third, execv
Forth, wait
*/


//this function make arg to argv and return argv's num.
//when argv's work is done, must free this memory allocation.
int split_string(char *arg, char *argv[], char spliter){
	int MAX_LENG = 256;
	
	int i = 0;
	int j = 0;
	int one_chr;
	char str[MAX_LENG];
	char *newstr;
	
	for (; one_chr = *arg++; ) {
		if ((char)one_chr == spliter) {
			str[j++] = '\0';
			newstr = (char*) malloc (sizeof(char) * j);
			strncpy(newstr, str, j);
			argv[i++] = newstr;
			j = 0;
		}
		else 
			str[j++] = (char)one_chr;
	}
	if (j > 0) {
		str[j++] = '\0';
		newstr = (char*) malloc (sizeof(char) * j);
		strncpy(newstr, str, j);
		argv[i] = newstr;
	}
	return i+1;
}



int mysystem(char *cmd) {
	//First, string parsing
	char *argv[MAX_CMD];
	int num = split_string(cmd, argv, ' ');
	argv[num] = NULL;	
	//Second, fork
	pid_t pid;
	int status;

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	
	//Third, exec
	if (pid == 0) {
		if(execvp(argv[0],argv) < 0 ) {
			perror("execvp");
			exit(1);
		}
		exit(0);
	}

	//Forth, wait
	if(wait(&status) < 0) {
		perror("waitpid");
		exit(1);
	}
	
	//Fifth, free memory.
	int k;
	for (k = 0 ; k < num; k++)
	{	
		free(argv[k]);
	}
}

void main() {
	//mysystem("ls -al");
    char *cmd = "ls -al";
	printf("---------mysystem-----------\n");
	mysystem(cmd);
	printf("----------system------------\n");
	system(cmd);
}
