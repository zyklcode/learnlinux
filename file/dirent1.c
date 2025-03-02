#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>

int main(int argc, char *argv[]){
	if(argc!=2){
		error(1, 0, "Right Usage: %s", argv[0]);
	}
	DIR* stream = opendir(argv[1]);
	if(!stream){
		error(1, errno, "opendir %s", argv[1]);
	}
	struct dirent *dir=NULL;
	while((dir=readdir(stream))!=NULL){
		printf("d_ino=%ld, d_off=%ld, d_reclen=%hu, d_type=%d, d_name=%s\n", dir->d_ino, dir->d_off, dir->d_reclen, dir->d_type, dir->d_name);
	}
	if(errno){
		error(1, errno, "readdir");
	}

	closedir(stream);
	return 0;
}
