#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 256


void printBinary(int num) {
	int mult2 = 1;
	char binary[256];

	while( num - mult2 >= 0) {
		mult2 *= 2;
	}
	mult2 /= 2;
	
	while(mult2 != 0){
		if (num - mult2 >= 0) {
			strcat(binary, "1");
			num -= mult2;
		}
		else
			strcat(binary, "0");
		mult2 /=2;
	}
	printf("%s\n",binary);
}

void main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s src", argv[0]);
		exit(1);
	}

	int num = atoi(argv[1]);
	
	printBinary(num);
}
