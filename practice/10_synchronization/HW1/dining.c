#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_MEN 5
#define NLOOPS 5

/*
	This program make program not to fall in deadlock.
	So, make all chopstick to be a semaphore, 
	then one process get chopstick anyone can't get.
	But, when all philosopher choose same time one chopstick,
	anyone can't eat food.
	Threrefore, This example is wrong.
*/


sem_t ChopStick[NUM_MEN];

void
ThreadUsleep(int usecs)
{
	pthread_cond_t		cond;
	pthread_mutex_t		mutex;
	struct timespec		ts;
	struct timeval		tv;

	if (pthread_cond_init(&cond, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	if (ts.tv_nsec >= 1000000000)  {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	if (pthread_mutex_lock(&mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  {
		perror("pthread_cond_timedwait");
		pthread_exit(NULL);
	}

	if (pthread_cond_destroy(&cond) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&mutex) < 0)  {
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}
}

// just thinck a few time.
void Thinking(int id) {
	printf("Phiosopher%d: Thinkig......\n", id);
	ThreadUsleep((rand()%200)*10000);
	printf("Philosopher%d: wandt to eat....\n", id);
}


// just eating a few time.
void Eating(int id) {
	printf("Philosopher%d: Eating.....\n", id);
	ThreadUsleep((rand()%100)*10000);
}

// all philosopher's action.
void DiningPhilosopher(int *pId) {
	int i;
	int id=*pId;
	for (i =0; i < NLOOPS; i++) {
		// do thinking
		Thinking(id);
		// get left chopstick
		if (sem_wait(&ChopStick[id]) < 0) {
			perror("sem_wait");
			exit(1);
		}
		// get right chopstick
		if (sem_wait(&ChopStick[(id+1)%NUM_MEN]) < 0) {
			perror("sem_wait");
			exit(1);
		}
		// go eat
		Eating(id);
		
		// put left chopstick
		if (sem_post(&ChopStick[id]) < 0) {
			perror("sem_post");
			exit(1);
		}

		// put right chopstick
		if (sem_post(&ChopStick[(id+1)%NUM_MEN]) < 0) {
			perror("sem_post");
			exit(1);
		}
	}
	printf("Philosopher%d: thinking & eating %d times....\n", id, i);
	
	pthread_exit(NULL);
}

void main() {
	pthread_t tid[NUM_MEN];
	int i, id[NUM_MEN];

	srand(0x8888);
	// make five semaphore for chopstick with initialization to 1.
	for (i = 0; i < NUM_MEN; i++) {
		if (sem_init(&ChopStick[i], 0, 1) < 0) {
			perror("sem_init");
			exit(1);
		}
		id[i] = i;	
	}
	
	// make 5 threads.
	for (i = 0; i < NUM_MEN; i++){
		if(pthread_create(&tid[i], NULL, (void *)DiningPhilosopher, (void *)&id[i]) < 0) {
			perror("pthread_create");
			exit(1);
		}
	}
	
	// wait end of all 5 threads.
	for (i = 0 ; i < NUM_MEN; i++) {
		if(pthread_join(tid[i], NULL) < 0) {
			perror("pthread_join");
			exit(1);
		}
	}
	
	// destory all semaphore
	for (i = 0; i < NUM_MEN; i++) {
		if (sem_destroy(&ChopStick[i]) < 0) {
			perror("sem_destroy");
		}
	}
}
