#include <stdio.h>

void main(int argc, char* argv[]) {

	int i;
	for (i = 0 ; i < argc; i++)
		printf("argv[%d]=%s\n", i , argv[i]);
}


/*
[description] : this program show all argv puted by user

if user put ./args hi hello good, this argv's size is 4.
So argc == 4 and argv[0] = "./args", argv[1] == "hi" and so on.
and print all argv's element.
*/
