#include <stdio.h>

void main() {
	int i = 9;
	int j;
	for (; i > 0 ; i--) {
		for (j = 1; j <= i; j++) {
			printf("%d",j);
			printf(" ");
		}
		printf("\n");
	}
}
