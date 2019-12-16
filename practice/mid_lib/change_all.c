#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void change_all(char* str, char a, char b) {
	char *changer = str;
	while((changer = strchr(changer, a)) != NULL) {
		*changer = b;
	}
}


//ex
/*
void main(){
	char hello[100] = "hello, world!";
	change_all(hello,'l','g');

	printf("%s\n", hello);
}
*/
