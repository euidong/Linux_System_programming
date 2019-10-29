/*
This program create 2 file.
One file is created and has 6 authentication. (user write/read , group write/read, other write/read)
Second file is created and has 2 authentication (user write/read).
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void main() {
	// no limit any authentication.
	umask(0);
	if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0 ) {
		perror("create");
		exit(1);
	}

	// limit group read/write and other read/write
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0 ) {
        perror("create");
        exit(1);
    }	
}
