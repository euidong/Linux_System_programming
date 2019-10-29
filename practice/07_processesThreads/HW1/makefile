CC = gcc
CFLAGS = 
LDFLAGS = -lpthread

.SUFFIXES = .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<
 

BASE = fork1 fork exit wait race worace env exec system cmd_i cmd_p 

THREAD = thread cmd_t

all : $(BASE) $(THREAD)

fork1 : fork1.c
	$(CC) -o $@ $<

fork : fork.c
	$(CC) -o $@ $<

exit : exit.c
	$(CC) -o $@ $<

wait : wait.c
	$(CC) -o $@ $<

race : race.c 
	$(CC) -o $@ $<

worace : worace.c
	$(CC) -o $@ $<

env : env.c
	$(CC) -o $@ $<

exec : exec.c
	$(CC) -o $@ $<

system : system.c
	$(CC) -o $@ $<

cmd_i : cmd_i.c
	$(CC) -o $@ $<

cmd_p : cmd_p.c
	$(CC) -o $@ $<


thread : thread.c
	$(CC) -o $@ $< $(LDFLAGS)

cmd_t : cmd_t.c
	$(CC) -o $@ $< $(LDFLAGS)


clean: 
	rm -rf *.o $(BASE) $(THREAD)
