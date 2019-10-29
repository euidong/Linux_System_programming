/*
This program print list of current directory's all file by two version, one is just currenctory file, the other include in directory file.

1. print all files <-- same myls.c

2. find all directory if directory exist go 3 step else exit.
3. read directory and go first step. 

end case : directory not exist.(except . , .. )
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH 256


// recursive function
// end case : directory not exist.(except . , .. )
//
void print_inDirectory_files(char *path){
	DIR *DP;
	struct dirent *element;
	char want_go[MAX_PATH];
	struct stat stat_buf;
	
	//open directory
	if((DP = opendir(path)) == NULL) {
		perror("opendir");
		exit(1);
	}

	//print current directory name
	printf("\n%s:\n", path);
	
	//print all element in current directory
	while((element = readdir(DP)) != NULL) {
		if (strcmp(".",element->d_name)== 0 || strcmp("..",element->d_name) == 0) 
			continue; 
		printf("%s\n",element->d_name);
	}
	
	//rewind directory pointer
	rewinddir(DP);

	//find directory in current directory
	while(element = readdir(DP)) {
		// ignore . & .. directory
		if (strcmp(".", element->d_name) == 0 || strcmp("..", element->d_name) == 0)
			continue;
		//current directory path + file name = file path
		strcpy(want_go, path);
		strcat(want_go, "/");
		strcat(want_go, element->d_name);
		
		//get lstat from file
		if(lstat(want_go, &stat_buf) < 0) {
			perror("lstat");
			exit(1);
		}
		
		// if this file is directory go inside.
		if (S_ISDIR(stat_buf.st_mode))
			print_inDirectory_files(want_go);
	}
	
	// close directory
	closedir(DP);
}



void main(){
	print_inDirectory_files(".");
}

