#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SIZE 256

void *countingThread(void * input) {
	char *file_name = (char *)input;
	int counter = 0;
	char checker;

	FILE *src;
	if (!(src = fopen(file_name, "r"))) {
		perror("fopen");
		exit(1);
	}

	while((checker = fgetc(src)) != EOF) {
		if (checker > 96 && checker < 122) {
			counter++;
		}
	}
	printf("%s: %d\n", file_name, counter);
	fclose(src);
}


void main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Usage: %s file1 file2 ... filen", argv[0]);
		exit(1);
	}
	DIR *dp;
	struct dirent *dep;

	char *split[2];

	if ((dp = opendir(".")) == NULL) {
		perror("opendir");
	}



	pthread_t tid[100];
	int i;
	for (i = 1 ; i < argc; i++) {
		pthread_create(&tid[i - 1], NULL, countingThread, (void *)argv[i]);
	}
    for (i = 1 ; i < argc; i++) {
        pthread_join(tid[i - 1], NULL);
    }

}
