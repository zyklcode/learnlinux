#include<stdio.h>
#include<error.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include <sys/stat.h>



void rmdir2(const char * path){
    DIR* stream = opendir(path);
    struct dirent* cur=NULL;
    while((cur=readdir(stream))!=NULL){
        char *filename = cur->d_name;
        if(strcmp(".", filename)==0 || strcmp("..", filename)==0){
            continue;
        }
        char subpath[128] = {'\0'};
        sprintf(subpath, "%s/%s", path, filename);
        if(cur->d_type == DT_DIR){
            rmdir2(subpath);
        }else{
            if(unlink(subpath)){
                error(1, errno, "unlink %s", subpath);
            }
        }
    }

    if(closedir(stream)){
        error(1, errno, "closedir");
    }

    if(errno){
        error(1, errno, "readdir");
    }

    if(rmdir(path)){
        error(1, errno, "rmdir %s", path);
    }
}

int main(int argc, char* argv[]){
    if(argc!=2){
        error(1, 0, "Right Usage: %s [[.] [..] [path]]", argv[0]);
    }

    rmdi2(argv[1]);
    return 0;
}