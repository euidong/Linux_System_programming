#include <stdlib.h>
#include <stdio.h>

void main(int argc, char *argv[]) {
	
	FILE *src;	
	char checker;
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s src dst", argv[0]);
		exit(1);
	}
	
	if (!(src = fopen(argv[1], "r+t"))) {
		perror("fopen");
		exit(1);
	}

	while((checker = fgetc(src)) != EOF) {
		if (checker > 96 && checker < 122) {
			checker -= 32;
			fseek(src,-1L ,SEEK_CUR);
			fputc(checker, src);
		}
	}

	fclose(src);
}
