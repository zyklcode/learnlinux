#include<stdio.h>
#include<error.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc!=3){
		error(1, 0, "Right Usage: %s file length", argv[0]);
	}
	off_t length;
	sscanf(argv[2], "%ld", &length);
	int fd = open(argv[1], O_RDWR);
	if(fd==-1){
		error(1, errno, "open");
	}
	if(ftruncate(fd, length)==-1){
		error(1, errno, "ftruncate %d", fd);
	}
	close(fd);
	return 0;
}
