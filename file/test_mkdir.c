#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<error.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char* argv[]){
	// ./test_mkdir dir mode
	if(argc!=3){
		error(1, 0, "Right Usage: %s dir mode", argv[0]);
	}
	mode_t mode;
	sscanf(argv[2], "%o", &mode);
	int err = mkdir(argv[1], mode);
	if(err){
		error(1, errno, "mkdir error use");
	}
	return 0;
}
