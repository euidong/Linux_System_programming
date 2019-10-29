#include <stdio.h>
#include <stdlib.h>
/*
This program copy one file, and paste another file.

First, it check whether argc is 3, if not print usage and exit this program.

Second, it open argv[1]'s file as "read text". if can't open this file print error and exit this program.

Third, it open argv[2]'s file as "write text". if can't open this file print error and exit this program.

Forth, it read argv[1] file and write argv[2] file untill argv[1] file's end of file or can't read this file.
*/

void main(int argc, char *argv[]) {

	FILE *src, *dst;
	int ch;


	if (argc != 3) {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	while((ch = fgetc(src)) != EOF) {
		fputc(ch, dst);
	}

	fclose(src);
	fclose(dst);
}
