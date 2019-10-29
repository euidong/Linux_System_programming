#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 256

/*
This program copy argv[1] file and paste to argv[2] file.

First, it check how many argv put by user.
if argc is not 3, print usage and exit this program.

Second, it open argv[1] file as "read text".
if can't do that, print error and exit this program.

Third, also open argv[2] file. it same second.

Fourth, it gets from argv[1] file and puts to argv[2] file untill can't get from argv[1] file
*/

void main(int argc, char *argv[]) {

	FILE *src, *dst;
	char buf[MAX_BUF];

	if (argc != 3) {
		fprintf(stderr,"Usage: %s source destination\n", argv[0]);
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

	while((fgets(buf, MAX_BUF, src)) != NULL) {
		fputs(buf, dst);
	}

	fclose(src);
	fclose(dst);
}
