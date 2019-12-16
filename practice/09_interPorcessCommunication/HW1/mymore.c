#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
	This program is same operation with "ls -l | more".
	more get stdin and print in order page.
*/

int main() {
	int fd[2];
	pid_t pid;
	
	// make pipe
	if (pipe(fd) == -1 ) {
		perror("pipe");
		exit(1);
	}
	
	// make process.
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	//child
	else if (pid == 0) {
		// close stdout.
		close(1);
		// close pipe in.
		close(fd[0]);
		
		// duplicate stdout to pipe out.
		if (dup(fd[1]) == -1) {
			perror("dup");
			exit(1);
		}

		// execution "ls -l"
		if((execlp("ls", "ls", "-l", NULL)) == -1) {
			perror("execlp");
			exit(1);
		}
	}
	
	//parent
	else {
		// close stdin.
		close(0);
		// close pipe out.
		close(fd[1]);

		// duplicate stdin to pipe in.
		if(dup2(fd[0], 0) == -1) {
			perror("dup2");
			exit(1);
		}

		// more get pipe in.
		if((execlp("more", "more", NULL)) == -1) {
			perror("execlp");
			exit(1);
		}
	}

	return 0;
}
