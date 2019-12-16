#include <sys/types.h>
#include <unistd.h>

void TELL_WAIT(void); // make setting make two pipe
void TELL_PARENT(void); // parent tell to child using pipe
void WAIT_PARENT(void); // parent wait untill child tell to parent.
void TELL_CHILD(void); // child tell to parent using pipe.
void WAIT_CHILD(void); // child wait untill parent tell to child.
