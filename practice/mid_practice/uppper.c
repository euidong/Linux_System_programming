#include <stdio.h>
#include <string.h>

void strupper(char str[]) {
	int i = 0 ;
	int one_chr;
	char *make= "";

	while(str[i] != '\0'){
		one_chr = (int)str[i];
		if (one_chr >96 && one_chr < 122) 
		{	
			one_chr -= 32;
			str[i] = one_chr;	
		}
		i++;
	}
}


void main() {
	char hello[15] = "hello, world!";
	strupper(hello);
	printf("%s\n",hello);
}

