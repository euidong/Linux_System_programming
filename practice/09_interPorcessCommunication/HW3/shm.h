#define MY_ID 41 // my id
#define SHM_KEY (0x9000 + MY_ID) // shared memory's key
#define SHM_SIZE 1024 // shared memory size.
#define SHM_MODE (SHM_R | SHM_W | IPC_CREAT) // shared memory mode.
