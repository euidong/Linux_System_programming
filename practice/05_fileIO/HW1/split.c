#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MAX_BUF	1024

/*
This program split argv[1] file. and save half to argv[2] file, remains to argv[3]

First, it check argc is 4, if not print usage and exit it.

Second, it open 3 file. argv[1](read binary), argv[2](write binary), argv[3](write binary). if these are not exit print error and exit it.

Third, find end of file and get size of file.

Fourth, split argv[1] file. and half of it paste to argv[2] and so on. 
*/

long filesize(FILE *fp)
{
	long	cur, size;
	cur = ftell(fp); //keep current locatopn to return this location
	fseek(fp, 0L, SEEK_END); 
	size = ftell(fp); //save size of file 
	fseek(fp, cur, SEEK_SET);
	return(size);
}


void main(int argc, char *argv[])
{
	FILE	*src, *dst1, *dst2;
	char	buf[MAX_BUF];
	int		count, size;

	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst1 = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst2 = fopen(argv[3], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	size = filesize(src) / 2;

	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src); 
		fwrite(buf, 1, count, dst1);
		size -= count;
	}

	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst2);
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);
}
