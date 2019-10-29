#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 256

/*
This program print all file's element and show line of this element.

First, it check whether argc is 2. if not print this Usage and exit this program.

Second, it open argv[1] file as "read text". if can't open this file, print error and exit this program.

Third, it get lines from argv[1] file untill end of file or can't read this file.
and print line number and argv[1]'s line
*/



void main(int argc, char *argv[]) {
	FILE *fp;
	char buf[MAX_BUF];
	int line;

	if (argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "rt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	line =1;
	while(fgets(buf, MAX_BUF, fp) != NULL){
		printf("%4d: %s", line++, buf);
	}

	fclose(fp);
}
