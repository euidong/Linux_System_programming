#define MY_ID 41
#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 0x8000 + MY_ID
#define MAX_BUF 100


typedef struct {
	int id;
	char cmd[10];
}MsgType;

