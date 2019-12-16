#include <stdio.h>
#include <string.h>

void del(char str[]) {
	int i;
	for (i = 1 ; i < strlen(str); i++){
		str[i-1] = str[i]; 
	}
	str[i - 1] = '\0';
}




void main() {
	char str[20] = "heldsadsalo";
	del(str);
	puts(str);
}

