#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<error.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char* argv[]){
	// ./test_rmdir dir
	if(argc!=2){
		error(1, 0, "Right Usage: %s dir", argv[0]);
	}
	int err = rmdir(argv[1]);
	if(err){
		error(1, errno, "rmdir error use");
	}
	return 0;
}
