#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void del(char str[]) {
	sprintf(str,"%s",(str + 1));
}

void main() {
	char str[20] = "Hello";
	del(str);
	puts(str);
}

