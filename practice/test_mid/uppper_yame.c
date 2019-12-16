#include <stdio.h>
#include <string.h>

void strupper(char str[]) {
	int i = 0 ;
	int one_chr;
	while(str[i] != '\0'){
		one_chr = (int)str[i];
		if (one_chr >96 && one_chr < 122) 
			putc(one_chr -32 , stdout);
		else 
			putc(one_chr, stdout);
		i++;
	}
	printf("\n");
}


void main() {
	char *hello = "hello, world!";

	strupper(hello);
}

