#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#define MAX_BUF 256

void main() {
	DIR *dp;
	struct dirent *dep;
	struct stat file_stat;

	char *file_name[MAX_BUF];
	int file_num = 0;
	if ((dp = opendir(".")) == NULL) {
		perror("opendir");
		exit(0);
	}

	while(dep = readdir(dp)) {
		if (strcmp(".", dep->d_name) == 0)
			continue;
		else if(strcmp(dep->d_name, "..") == 0)
			continue;
		file_name[file_num++] = dep->d_name;
	}
	int i;
	for (i = 0; i < file_num;i++) {
		if (lstat(file_name[i], &file_stat) < 0){
			perror("lstat");
			exit(1);
		}
		if (file_stat.st_size > 500) {
			printf("%s size : %ld\n",file_name[i], file_stat.st_size);		
		}
	}
}
