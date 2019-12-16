#define MY_ID 41
#define SERV_PORT 0x8000 + MY_ID
#define SERV_ADDR "127.0.0.1"
#define MAX_BUF 256

typedef struct {
	int id;
	char buf[MAX_BUF];
} MsgType;
