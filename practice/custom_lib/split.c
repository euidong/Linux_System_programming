#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// this function make from string to two string as distinguish by one character.
// and, if you end of use this function, you must free string array.
// this function return a number of splits.

int split(char *arg, char *split[2], char cutter) {
    int MAX_LENG = 256;

    int i = 0;
    int j = 0;
    int one_chr;
    char str[MAX_LENG];
    char *newstr;
	int is_cutting= 0;
	int cutter_location = -1;
    for (; one_chr = *arg++; ) {
        if ((char)one_chr == cutter && is_cutting == 0) {
            cutter_location = j;
			is_cutting = 1;
			str[j++] = '\0';
            newstr = (char*) malloc (sizeof(char) * j);
            strncpy(newstr, str, j);
            split[i++] = newstr;
			j = 0;
        }
        else
            str[j++] = (char)one_chr;
    }
	str[j++] ='\0';
    if (j > 1) {
        newstr = (char*) malloc (sizeof(char) * j);
        strncpy(newstr, str, j);
        split[i] = newstr;
    }
    return cutter_location;
}


// example
/*
void main(){
	char *good ="hello, world!    it's good day";
	char *hi[2];
	if (split(good,hi,' ') != -1) {
		printf("%s\n",hi[0]);
		printf("%s\n",hi[1]);
	}
	int i;
	for (i = 0 ; i < 2 ; i++)
		free(hi[i]);
}
*/
