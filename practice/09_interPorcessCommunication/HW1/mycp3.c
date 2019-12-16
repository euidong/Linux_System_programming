#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
	This program copy file. and paste to other file.
    Especially, using memory maped file.
	This way same result to using file read & write system call.
	But, this speed is very very faster than read & write.
	Because, this way didn't have overhead between application and OS.
	File read & write occur among application, OS, memory and HDD.
	So, application request OS then, OS write memory to HDD, every time.
	Memory maped file just write one, OS do all copy between memory and HDD not application.
*/
void main(int argc, char *argv[])
{
	int			fdin, fdout;
	char		*src, *dst;
	struct stat	statbuf;

	// check arguments is right.
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	// open file to read.
	if ((fdin = open(argv[1], O_RDONLY)) < 0)  {
		perror("open");
		exit(1);
	}

	// open file to write.
	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)  {
		perror("open");
		exit(1);
	}

	// get file data from file to read.
	if (fstat(fdin, &statbuf) < 0)  {
		perror("fstat");
		exit(1);
	}

	// set file to write size same with file to read.
	if (lseek(fdout, statbuf.st_size-1, SEEK_SET) < 0)  {
		perror("lseek");
		exit(1);
	}
	write(fdout, "", 1);

	// memory map with file to read.
	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) 
		== (caddr_t) -1)  {
		perror("mmap");
		exit(1);
	}

	// memory map with file to write.
	if ((dst = mmap(0, statbuf.st_size, PROT_WRITE, MAP_SHARED, fdout, 0)) 
		== (caddr_t) -1)  {
		perror("mmap");
		exit(1);
	}
	
	// copy file to read to file to write.(just one line)
	memcpy(dst, src, statbuf.st_size);

	close(fdin);
	close(fdout);
}
