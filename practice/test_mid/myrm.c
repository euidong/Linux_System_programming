#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

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

void main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dep;
	
	char *split[2];

	if((dp = opendir(".")) == NULL) {
		perror("opendir");
	}

	if (argc < 2) {
		printf("Usage: %s file1 file2 ..... filen\n", argv[0]);
		exit(1);
	}
	int i;
	for (i = 1; i < argc; i++) {
		if(check_asta(argv[i])) {
			if (spliter(argv[i], split, '*') == 1) {
				while (dep = readdir(dp)){
					if(strlen(split[0]) -1 == in_string(dep->d_name, split[0]))
						remove(dep->d_name);
				}
			}
			else {
				while (dep = readdir(dp)){
					if(strlen(dep->d_name) -1 == in_string(dep->d_name, split[1]))
						remove(dep->d_name);
				}
			}
		}
		else {
			if(remove(argv[i]) < 0) {
				perror("remove");
				exit(1);
			}
		}
	}

	for (i = 0; i < 2; i++){
		free(split[i]);
	}
}
