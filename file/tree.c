#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include<string.h>

int num_dirs = 0;
int num_files = 0;

void print_space(int layer){
	for(int i=0;i<layer;i++){
		putchar('\t');
	}
}

void tree(const char * path, int layer){
	print_space(layer);
	puts(path);
	DIR * stream = opendir(path);
	if(!stream){
		error(1, 0, "opendir");
	}
	struct dirent *cur=NULL;
	while((cur=readdir(stream))!=NULL){
		char *filename = cur->d_name;
		if(strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0){
			continue;
		}
		if(cur->d_type == DT_DIR){
			// 拼接路径
			char subpath[128] = {'\0'};
			sprintf(subpath, "%s/%s", path, filename);
			num_dirs++;
			tree(subpath, layer+1);
		}else{
			print_space(layer+1);
			num_files++;
			puts(cur->d_name);
		}

	}
	closedir(stream);
	if(errno){
		error(1, 0, "readdir");
	}
}


int main(int argc, char *argv[]){
	if(argc>=3){
		error(1, 0, "Right Usage: %s [path]", argv[0]);
	}
	if(argc==1){
		tree(".", 0);
	}else{
		tree(argv[1], 0);
	}
	return 0;
}
