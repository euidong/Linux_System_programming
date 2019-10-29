/*
This program change "bar" and "foo" file's authentication. 
bar's group write authentication is turn off.
foo's user write/read and group write/read authentication is turn off.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

void main() {
	struct stat statbuf;
	
	//get bar's stat 
	if (stat("bar", &statbuf) <0) {
		perror("stat");
		exit(1);
	}
	
	//change bar's write group authorization.
	if (chmod("bar", statbuf.st_mode & ~S_IWGRP) < 0) {
		perror("chmod");
		exit(1);
	}
	
	//set foo's user read write, group read write authorization on.
	if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) < 0) {
		perror("chmod");
		exit(1);
	}
}
