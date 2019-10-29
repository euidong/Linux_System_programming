#include <stdio.h>
#include <string.h>

enum { FALSE, TRUE };

/*
This program chage '\t' to '    '. 
*/

void conv(char *fname)
{
	FILE	*src, *dst;
	char	fdest[40];
	int		ch, first;

	//open file
	if ((src = fopen(fname, "rt")) == NULL)  {
		perror("fopen");
		return;
	}

	//fdest = fname + ".t"
	strcpy(fdest, fname);
	strcat(fdest, ".t");

	//fdest file open.
	if ((dst = fopen(fdest, "wt")) == NULL)  {
		perror("fopen");
		return;
	}

	first = TRUE;
	//scan all file and get '\t' and chage it to '    '
	while ((ch = fgetc(src)) != EOF)  {
		if (first && ch == '\t')  {
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
		}
		else  {
			fputc(ch, dst);
			if (first)
				first = FALSE;
			if (ch == '\n')
				first = TRUE;
		}
	}

	fclose(src);
	fclose(dst);
}

void main(int argc, char *argv[])
{
	//while argc > 0
	while (--argc)  {
		conv(argv[argc]);
	}
}
