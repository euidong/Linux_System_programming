#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
/*
This program get data from test.in which distinguished 3 line, and put data to test.out which merge every 3 line to 1 line.

First, it check argc is 3. if not print usage and exit it.

Second, open files, argv[1] by read text argv[2] by write binary,if can't do print error and exit it.

Third, get data from argv[1] file and put data to argv[2] file.
it get 3 line data once, and put these by one line to argv[2] file.
*/

void main(int argc, char *argv[]) {
	FILE	*src, *dst;
	Record	rec;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source dest\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while (fgets(rec.stud, SMAX, src))  {
		*strchr(rec.stud, '\n') = '\0';
		fgets(rec.num, NMAX, src);
		*strchr(rec.num, '\n') = '\0';
		fgets(rec.dept, DMAX, src);
		*strchr(rec.dept, '\n') = '\0';

		fwrite(&rec, sizeof(rec), 1, dst);
	}

	fclose(src);
	fclose(dst);
}

