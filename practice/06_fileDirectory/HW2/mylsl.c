/*
This program implement ls -l.
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

#define MAX_BUF 1024

void print_FileType(struct stat file_stat){
	if (S_ISDIR(file_stat.st_mode))
		printf("d");
	else if (S_ISLNK(file_stat.st_mode))
		printf("l");
	else 
		printf("-");
}

void print_FileAuthentication(struct stat file_stat) {
	if(file_stat.st_mode&(S_IRUSR))
		printf("r");
	else
		printf("-");
	if(file_stat.st_mode&(S_IWUSR))
		printf("w");
	else
		printf("-");
	if(file_stat.st_mode&(S_IXUSR))
		printf("x");
	else
		printf("-");	
	if(file_stat.st_mode&(S_IRGRP))
        printf("r");
    else
        printf("-");
    if(file_stat.st_mode&(S_IWGRP))
        printf("w");
    else
        printf("-");
    if(file_stat.st_mode&(S_IXGRP))
        printf("x");
    else
        printf("-");
	if(file_stat.st_mode&(S_IROTH))
        printf("r");
    else
        printf("-");
    if(file_stat.st_mode&(S_IWOTH))
        printf("w");
    else
        printf("-");
    if(file_stat.st_mode&(S_IXOTH))
        printf("x");
    else
        printf("-");
}

void print_LinkNumber(struct stat file_stat){
	printf(" %ld\t", file_stat.st_nlink);
}

void print_UserName(struct stat file_stat) {
	struct passwd *pwd = getpwuid(file_stat.st_uid);
	printf("%s\t", pwd->pw_name);
}

void print_GroupName(struct stat file_stat) {
	struct group *g = getgrgid(file_stat.st_gid);
	printf("%s\t", g->gr_name);	
}

void print_BlockSize(struct stat file_stat) {
	printf("%ld\t", file_stat.st_size);
}

void print_Month(int month) {
	if (month == 0) {
		printf("Jan");
	}
	else if (month == 1) {
		printf("Feb");
	}
    else if (month == 2) {
        printf("Mar");
    }
    else if (month == 3) {
        printf("Apr");
    }
    else if (month == 4) {
        printf("May");
    }
    else if (month == 5) {
        printf("Jun");
    }
    else if (month == 6) {
        printf("Jul");
    }
    else if (month == 7) {
        printf("Aug");
    }
    else if (month == 8) {
        printf("Sep");
    }
    else if (month == 9) {
        printf("Oct");
    }
    else if (month == 10) {
        printf("Nov");
    }
    else if (month == 1) {
        printf("Dec");
    }

}

void print_LastModifiedTime(struct stat file_stat) {
	struct tm *date = localtime(&file_stat.st_mtime);
	print_Month(date->tm_mon);
	printf(" %d ", date->tm_mday);
	if(date->tm_hour < 10)
		printf("0");
	printf("%d:", date->tm_hour);
	if(date->tm_min < 10)
		printf("0");
	printf("%d", date->tm_min);	
}

void print_FileName(char *file_name) {
	printf(" %s\n", file_name);
}

int partition(char *file_name[], int front, int back){
	int middle = front;
	char *pivot = file_name[front];
	int i;
	char* tmp;
	for (i = front+1; i <= back; i++) {
		if(strcmp(pivot,file_name[i]) > 0){
			tmp = file_name[++middle];
			file_name[middle] = file_name[i];
			file_name[i] = tmp;
		}
	}
	file_name[front] = file_name[middle];
	file_name[middle] = pivot;
	
	return middle;
}

void quickSort(char *file_name[], int front, int back){
	if (front+1 == back) {
		if(strcmp(file_name[front], file_name[back]) > 0) {
			char *tmp = file_name[front];
			file_name[front] = file_name[back];
			file_name[back] = tmp;
		}
		return;
	}
	else if (front >= back) 
		return;
	int middle = partition(file_name, front, back);
	quickSort(file_name, front, middle-1);
	quickSort(file_name, middle+1, back);
}

void main() {
	DIR *dp;
	struct dirent *dep;
	struct stat file_stat;	
	
	char *file_name[MAX_BUF];
	int file_num = 0;
	int j;

	if(!(dp = opendir("."))) {
		perror("opendir");
		exit(1);
	}
	
	while(dep = readdir(dp)) {
		if(dep->d_name[0] == '.')
			continue;
		file_name[file_num++] = dep->d_name;
	}
	
	quickSort(file_name, 0, file_num - 1);
	for (j =0; j < file_num; j++) {
		if(lstat(file_name[j], &file_stat) < 0) {
			perror("lstat");
			exit(1);
		}
		print_FileType(file_stat);
		print_FileAuthentication(file_stat);
		print_LinkNumber(file_stat);
		print_UserName(file_stat);
		print_GroupName(file_stat);
		print_BlockSize(file_stat);
		print_LastModifiedTime(file_stat);
		print_FileName(file_name[j]);
	}

}

