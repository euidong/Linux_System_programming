#include <stdio.h>

void main() {
	char c, s[80];
	int i;
	long l;
	float f;
	double d;

	scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d);
	
	printf("Output : %c %s %d %ld %.4f %.2lf\n", c,s,i,l,f,d);

	
	c = getchar();
	putchar(c);

	fgets(s, 80, stdin);
    puts(s);
}


/*
This file is used to print all words puted by user.

user can put one character , one integer, one long integer, one float type number, one double type number.
then, program print all words puted by user.
when this operation ended, user can put one character, and one word.

finally, this program print character , and word.
*/
