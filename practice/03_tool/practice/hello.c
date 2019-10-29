#include <stdio.h>
#include "mystrcpy.h"

void main()
{
	char str[80];

	mystrcpy(str, "Hello");
	printf("good!, ");
	printf("%s",str);
	printf(", world\n");
	
}


