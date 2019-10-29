/*
This program print current directory's absolute path.
*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_PATH 256

void main() {
	char path[MAX_PATH];	

	// get absolute path.
    if (getcwd(path,MAX_PATH) == NULL) {
        perror("getcwd");
        exit(1);
    }

	printf("%s\n", path);
}
