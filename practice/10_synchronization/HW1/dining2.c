#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

#define NUM_MEN 5
#define NLOOPS 5

#define LEFT(i) ((i+NUM_MEN-1)%NUM_MEN)
#define RIGHT(i) ((i+1)%NUM_MEN)

/*
	This program solve all deadlock problem in dinning philosopher problem.
    1. thinking
	2. test whether i can eat.(two chopstick is exist.)
	3. if not, wait. the other is do eating then test each sides.
	4. and go thinking(1)
*/

// state are thinking / eating / hungry.
enum { THINKING, EATING, HUNGRY};

sem_t Philosopher[NUM_MEN];
sem_t Mutex;

int State[NUM_MEN];


void ThreadUsleep(int usecs) {
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

// just thinking a few time.
void Thinking(int id) {
	printf("Philosopher%d: Thinking....\n", id);
	ThreadUsleep((rand()%200)*10000);
	printf("Philosopher%d: Want to eat.....\n", id);
}

// just eating a few time.
void Eating(int id) {
	printf("Philosopher%d: Eating.....\n", id);
	ThreadUsleep((rand()%100)*10000);
}

// this function test whether i can eat.
// if can, do make philosopher semaphore to 1 and make state eating.
void Test(int id) {
	if (State[id] == HUNGRY && State[LEFT(id)] != EATING && State[RIGHT(id)] != EATING) {
		State[id] = EATING;
		if (sem_post(&Philosopher[id]) < 0) {
			perror("sem_post");
			pthread_exit(NULL);
		}
	}
}

// if can eat, pick up two chopstick.
// And make table critical section.
void PickUp(int id) {
	if (sem_wait(&Mutex) < 0) {
		perror("sem_wait");
		exit(1);
	}
	State[id] = HUNGRY;
	Test(id);

	if (sem_post(&Mutex) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}

	if (sem_wait(&Philosopher[id]) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}
}

// before putdown chopsticks, test each sides state.
void PutDown(int id) {
	if (sem_wait(&Mutex) < 0) {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	State[id] = THINKING;
	Test(LEFT(id));
	Test(RIGHT(id));

	if (sem_post(&Mutex) < 0) {
		perror("sem_post");
		pthread_exit(NULL);
	}
}

// 5time's thinking and eating.
void DiningPhilosopher(int *pId) {
	int i;
	int id= *pId;

	for (i=0; i < NLOOPS; i++) {
		Thinking(id);
		PickUp(id);
		Eating(id);
		PutDown(id);
	}

	printf("Philosopher%d: thinking & eating %d times.....\n", id, i);
	pthread_exit(NULL);
}

// it's same to dinning.c
void main() {
	pthread_t tid[NUM_MEN];
	int i, id[NUM_MEN];

	for (i = 0 ; i< NUM_MEN; i++) {
		if(sem_init(&Philosopher[i],0,0) < 0) {
			perror("sem_init");
			exit(1);
		}
		id[i] = i;	
	}
	if (sem_init(&Mutex, 0, 1) < 0) {
		perror("sem_init");
		exit(1);
	}
    for (i = 0 ; i< NUM_MEN; i++) {
		if (pthread_create(&tid[i], NULL, (void*)DiningPhilosopher, (void *)&id[i]) < 0) {
			perror("pthread_create");
			exit(1);
		}
    }
    for (i = 0 ; i< NUM_MEN; i++) {
		if (pthread_join(tid[i], NULL) < 0) {
			perror("pthread_join");
			exit(1);
		}
    }
    for (i = 0 ; i< NUM_MEN; i++) {
		if (sem_destroy(&Philosopher[i]) < 0) {
			perror("sem_destroy");
			exit(1);
		}
    }
	if (sem_destroy(&Mutex) < 0) {
		perror("sem_destroy");
		exit(1);
	}
}
