CC = gcc
CFLAGS =
LDFLAGS =

.SUFFIXES : .c .o
.c .o :
	$(CC) -o ${CFLAGS} $@ $< $(LDFLAGS)

ALL = stat umask chmod myln mysln myrm mymv mymd myrd myls mylsr mycd mypwd

all: $(ALL)

clean:
	rm -rf *.o $(ALL)

