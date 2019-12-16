#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// make semaphore with key.
int semInit(key_t key);
// initialize semaphore value.
int semInitValue(int semid, int value);
// wait.
int semWait(int semid);
// if semaphore is 0, not wait.
int semTryWait(int semid);
// signal.
int semPost(int semid);
// get semaphore's value
int semGetValue(int semid);
// remove semaphore
int semDestroy(int semid);

