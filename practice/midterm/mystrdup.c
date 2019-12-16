#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *newstr;

void freeing() {
	free(newstr);
}


char *strdup(const char *s) {
	newstr = (char *) malloc (sizeof(char) * strlen(s));
	strcpy(newstr, s);
	atexit(freeing);

	return newstr;
}


void main(){
	char str1[] = "Hello World!";
	char *str2 = strdup(str1);
	puts(str2);
}
