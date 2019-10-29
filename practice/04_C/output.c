#include <stdio.h>

void main()
{
	char c= 'a', s[] = "hello";
	int i = 100;
	long l = 9999;
	float f = 3.14;
	double d = 3.141592;
	int *p = &i;

	printf("Output: %c %s %d %#X %ld %.4f %.2lf %p\n", c,s,i,i,l,f,d,p);
	putchar(c);
	puts(s);
}

/*
This program print all words.
so will print Output: a hello 100 9999 3.14 3.141592 i's address.
*/ 
