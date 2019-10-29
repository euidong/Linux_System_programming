#include <stdio.h>
#include <stdlib.h>


void main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage : %s file", argv[0]);
		exit(1);
	}
	FILE *fp;
	int count =0;
	int one_chr;
	int before_space = 0;
	if ((fp = fopen(argv[1], "rt")) == NULL) {
		perror("fopen");
		exit(1);
	}
	if((one_chr = fgetc(fp)) != EOF) {
		if (one_chr == (int)' ' || one_chr == (int)'\n')
			before_space = 1;
		else
			count = 1;
	}
	while((one_chr = fgetc(fp)) != EOF) {
		if (one_chr == (int)' ' || one_chr == (int)'\n')
			before_space = 1;
		else {
			if (before_space) {
				before_space = 0;
				count++;
			}
		}
	}
	printf("%d\n", count);
	fclose(fp);
}
