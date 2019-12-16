#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SIZE 256


// if has a astarika, return astarika's location.
// and change arg cutted.
int check_asta(char *arg) {
    int i = 0;
    while(arg[i] == '\0') {
        if (arg[i] == '*')
            return 1;
        i++;
    }
    return 0;
}

int spliter(char *arg, char *split[], char cutter) {
    int MAX_LENG = 256;

    int i = 0;
    int j = 0;
    int one_chr;
    char str[MAX_LENG];
    char *newstr;

    for (; one_chr = *arg++; ) {
        if ((char)one_chr == cutter) {
            str[j++] = '\0';
            newstr = (char*) malloc (sizeof(char) * j);
            strncpy(newstr, str, j);
            split[i++] = newstr;
            j = 0;
        }
        else
            str[j++] = (char)one_chr;
    }
    if (j > 0) {
        str[j++] = '\0';
        newstr = (char*) malloc (sizeof(char) * j);
        strncpy(newstr, str, j);
        split[i] = newstr;
    }
    return i+1;
}

// if str1 include str2, return end of same point in str1.
// else return 0
int in_string(char* str1, char * str2){
    int i =0;
    int j =0;

    int len = strlen(str2);
    int same_num = 0;

    while(str1[i] != '\0') {
        if (str1[i++] == str2[j]) {
            j++;
            if (len == j)
                return i;
        }
        else
            j = 0;
    }
    return 0;
}


void *countingThread(void * input) {
	char *file_name = (char *)input;
	int counter = 0;
	char checker;

	FILE *src;
	if (!(src = fopen(file_name, "r"))) {
		perror("fopen");
		exit(1);
	}

	while((checker = fgetc(src)) != EOF) {
		if (checker > 96 && checker < 122) {
			counter++;
		}
	}
	printf("%s: %d\n", file_name, counter);
	fclose(src);
}


void main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Usage: %s file1 file2 ... filen", argv[0]);
		exit(1);
	}
	DIR *dp;
	struct dirent *dep;

	char *split[2];

	if ((dp = opendir(".")) == NULL) {
		perror("opendir");
	}



	pthread_t tid;
	int i;
	for (i = 1 ; i < argc; i++) {
        if(check_asta(argv[i])) {
            if (spliter(argv[i], split, '*') == 1) {
                while (dep = readdir(dp)){
                    if(strlen(split[0]) -1 == in_string(dep->d_name, split[0])) {
                        pthread_create(&tid, NULL, countingThread,(void *)dep->d_name);
						pthread_join(tid, NULL);
                	}
				}
            }
            else {
                while (dep = readdir(dp)){
                    if(strlen(dep->d_name) -1 == in_string(dep->d_name, split[1])){
                    	pthread_create(&tid, NULL, countingThread, (void *)dep->d_name);
					    pthread_join(tid, NULL);
					}
                }
            }
        }
		else {
			pthread_create(&tid, NULL, countingThread, (void *)argv[i]);
			pthread_join(tid, NULL);
		}
	}
}
