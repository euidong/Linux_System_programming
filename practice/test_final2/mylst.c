/*
This program print list of current directory's all file name.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_FILE 256

int partition(char *fileName[], int time[], int front, int back) {
	int middle = front;
	int pivot = time[front];
	int i;
	char *tmp;
	int temp;
	for (i = front+1; i <=back; i++) {
		if (pivot > time[i]) {
			tmp = fileName[++middle];
			fileName[middle] = fileName[i];
			fileName[i] = tmp;
			temp = time[middle];
			time[middle] = time[i];
			time[i] = temp;
		}
	}
	tmp = fileName[front];
	fileName[front] = fileName[middle];
	fileName[middle] = tmp;

	time[front] = time[middle];
	time[middle] = pivot;

	return middle;
}


void quickSort(char *fileName[], int time[],  int front, int back) {
	if (front+1 == back) {
		if (time[front] > time[back]) {
			char *tmp = fileName[front];
			fileName[front] = fileName[back];
			fileName[back] = tmp;
			int temp = time[front];
			time[front] = time[back];
			time[back] = temp;
		}
		return;
	}
	else if (front >= back)
		return;
	int middle = partition(fileName, time, front, back);
	quickSort(fileName, time, front, middle-1);
	quickSort(fileName, time, middle+1, back);
}


void main() {
	DIR *DP;
	struct dirent *list;
	struct stat file_stat;

	char *fileName[MAX_FILE];
	int fileNum = 0;
	int j;
	int fileModifyTime[MAX_FILE];

	//open directory
	if ((DP = opendir(".")) == NULL) {
		perror("opendir");
		exit(1);
	}

	// read data one by one file.
	while((list = readdir(DP)) != NULL) {
		if (list->d_name[0] == '.')
			continue;
		fileName[fileNum] = list->d_name;
		if (lstat(fileName[fileNum], &file_stat) < 0) {
			perror("lstat");
			exit(1);
		}
		fileModifyTime[fileNum++] = (int)file_stat.st_mtime;
	}

	// sorting
	quickSort(fileName, fileModifyTime, 0, fileNum -1);
	
	// printing
	for (j = 0 ; j < fileNum; j++) {
		printf("%s | %d\n", fileName[j], fileModifyTime[j]);
	}

	// close directory
	closedir(DP);
}
