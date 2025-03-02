#include<stdio.h>
#include<error.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

int num_files = 0;
int num_dirs = 0;

void tree(const char * path, int layer){
    DIR* stream = opendir(path);
    struct dirent* cur=NULL;
    while((cur=readdir(stream))!=NULL){
        char *filename = cur->d_name;
        if(strcmp(".", filename)==0 || strcmp("..", filename)==0){
            continue;
        }
        for(int i=0;i<4*layer;i++){
            putchar(' ');
        }
        puts(filename);
        if(cur->d_type == DT_DIR){
            char subpath[128] = {'\0'};
            sprintf(subpath, "%s/%s", path, filename);
            num_dirs++;
            tree(subpath, layer+1);
        }else{
            num_files++;
        }
    }

    closedir(stream);
    if(errno){
        error(1, errno, "readdir");
    }
}

int main(int argc, char* argv[]){
    if(argc>=3){
        error(1, 0, "Right Usage: %s [[.] [..] [path]]", argv[0]);
    }
    if(argc==1){
        puts(".");
        tree(".", 1);
    }

    if(argc==2){
        puts(argv[1]);
        tree(argv[1], 1);
    }

    printf("files: %d, dirs: %d\n", num_files, num_dirs);

    return 0;
}