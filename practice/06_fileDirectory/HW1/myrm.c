/*
This program remove file.
*/

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]) {
	// target file didn't exist.
	if (argc == 1) {
		printf("Usage: %s filename \n", argv[0]);
		exit(1);
	}

	int i ;

	// remove all argv file.
	for (i = 1 ; i < argc ; i++ ){
		if (remove(argv[i]) == 0)
			printf("remove %s\n", argv[i]);
		else
			printf("can't remove %s\n", argv[i]);	
	}

}
