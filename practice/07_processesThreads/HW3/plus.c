#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//This function sum to n from n+49
//and return this result.
void *plus(void *n) {
	int i;
	// if you don't declare static variable, can't get result.
    // because, function local variable can't keep their data.
	// so, must declare static or global.	
	static int sum = 0;
	int num = *(int *)n;
	for (i = 0 ; i < 50; i++) {
		sum += i+num;
	}
	return (void *)&sum;
}


void main() {
	pthread_t tid1, tid2;
	void *status;
	int num1 = 1;
	int num2 = 51;
	if (pthread_create(&tid1, NULL, (void*)plus, (void*)&num1) < 0) {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, (void*)plus, (void*)&num2) < 0) {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_join(tid1,NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}
	
	if (pthread_join(tid2,&status) < 0) {
		perror("pthread_join");
		exit(1);
	}
	
	printf("%d\n", *(int *)status);
}
