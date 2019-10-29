/*
This program print list of current directory's all file name.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void main() {
	DIR *DP;
	struct dirent *list;
	//open directory
	if ((DP = opendir(".")) == NULL) {
		perror("opendir");
		exit(1);
	}
	// read data one by one file.
	while((list = readdir(DP)) != NULL) {
		printf("%s\n",list->d_name);
	}
	//close directory
	closedir(DP);
}
