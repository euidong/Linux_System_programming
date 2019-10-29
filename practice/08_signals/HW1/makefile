CC = gcc
CFLAGS = 
LDFLAGS = -lpthread

.SUFFIXES: .c.o

.c.o:
	$(CC) -c $(CFLAGS) $<

BASE = alarm mysleep nonreent sig1 sig2
USE_THREAD = sig_thread cancel

all : $(BASE) $(USE_THREAD)

alarm : alarm.c
	$(CC) -o $@ $<

mysleep : mysleep.c
	$(CC) -o $@ $<

nonreent : nonreent.c
	$(CC) -o $@ $<

sig1 : sig1.c
	$(CC) -o $@ $<

sig2 : sig2.c
	$(CC) -o $@ $<

sig_thread : sig_thread.c
	$(CC) -o $@ $< $(LDFLAGS)

cancel : cancel.c
	$(CC) -o $@ $< $(LDFLAGS)


clean :
	rm -f *.o $(BASE) $(USE_THREAD)
