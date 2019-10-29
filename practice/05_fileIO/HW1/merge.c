#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024
/*
Thist program  get two file(argv[1], argv[2]) and put one merge file(argv[3]).

First, it check argc is 4. if not print usage and exit it.

Second, it open 3 file as  binary.(argv[1], argv[2], argv[3])

Third, it get buffer from two read file(argv[1], argv[2]) and put this to one write file. 
*/

void main(int argc, char *argv[]) {
	FILE	*src1, *src2, *dst;
	char	buf[MAX_BUF];
	int		count;

	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
		exit(1);
	}

	if ((src1 = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((src2 = fopen(argv[2], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst = fopen(argv[3], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while ((count = fread(buf, 1, MAX_BUF, src1)) != 0)  {
		fwrite(buf, 1, count, dst);
	}

	while ((count = fread(buf, 1, MAX_BUF, src1)) != 0)  {
		fwrite(buf, 1, count, dst);
	}

	fclose(src1);
	fclose(src2);
	fclose(dst);
}
