/*
This program print file's mode.
And print all stat this file.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void main (int argc, char *argv[]) {
	struct stat statbuf;
	char *mode;
	int i;


	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
		//get stat from argv[i]
		if (lstat(argv[i], &statbuf) < 0) {
			perror("lstat");
			continue;
		}
		if (S_ISREG(statbuf.st_mode))
			mode = "Regular";
		if (S_ISDIR(statbuf.st_mode))
			mode = "Directory";
		if (S_ISCHR(statbuf.st_mode))
			mode = "Character special";
		if (S_ISBLK(statbuf.st_mode))
			mode = "block special";
		if (S_ISFIFO(statbuf.st_mode))
			mode = "pipe or FIFO";
		if (S_ISLNK(statbuf.st_mode))
			mode = "symbolic link";
		if (S_ISSOCK(statbuf.st_mode))
			mode = "socket";
		printf("%s\n", mode);
		printf("\tst_mode = %d\n", statbuf.st_mode);
		printf("\tst_ino = %ld\n", statbuf.st_ino);
		printf("\tst_dev = %ld\n", statbuf.st_dev);
		printf("\tst_rdev = %ld\n", statbuf.st_rdev);
		printf("\tst_nlink = %ld\n", statbuf.st_nlink);
		printf("\tst_uid = %d\n", statbuf.st_uid);
		printf("\tst_gid = %d\n", statbuf.st_gid);
		printf("\tst_size = %ld\n", statbuf.st_size);
		printf("\tst_atime = %ld\n", statbuf.st_atime);
		printf("\tst_mtime = %ld\n", statbuf.st_mtime);
		printf("\tst_ctime = %ld\n", statbuf.st_ctime);
		printf("\tst_blksize = %ld\n", statbuf.st_blksize);
		printf("\tst_blocks = %ld\n", statbuf.st_blocks);
	}
}
