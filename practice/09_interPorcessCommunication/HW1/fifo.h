#define MAX_FIFO_NAME 32

#define SERV_FIFO "./.fifo"


// It include return Fifo file's name in order to return from server.
typedef struct {
	char returnFifo[MAX_FIFO_NAME];
	char data[128];
}	MsgType;
