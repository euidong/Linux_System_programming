#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function make from string to string array as distinguish by one character.
// and, if you end of use this function, you must free string array.
// this function return a number of splits.
int all_split(char *arg, char *split[], char cutter) {
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

	if (i == 0)
		return -1;
    return i+1;
}


// example
/*
void main(){
    char *good ="hello, world!    it's good day";
    char *hi[100];
	
	int split_num;
    if ((split_num = all_split(good,hi,' ')) == -1) {
        printf("error");
    }
    int i;
    for (i = 0 ; i < split_num ; i++) {
    	printf("%s\n", hi[i]);    
		free(hi[i]);
	}
}
*/
