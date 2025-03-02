#include <sys/mman.h>
#include<stdio.h>
#include<error.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MMAP_SIZE 4096

int main(int argc, char *argv[]){
    // ./mmap_cp src dst
    if(argc!=3){
        error(1, 0, "Usage: mmap_cp src dst");
    }

    int src_fd = open(argv[1], O_RDONLY);
    if(src_fd==-1){
        error(1, errno, "open %s", argv[1]);
    }

    int dst_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(dst_fd==-1){
        close(src_fd);
        error(1, errno, "open %s", argv[2]);
    }

    // 1.文件大小需要事先固定
    // 获取src的大小
    struct stat file_stat;
    if(fstat(src_fd, &file_stat)){
        error(1, errno, "fstat");
    }

    off_t file_size = file_stat.st_size;
    // 将dst文件的大小设置为st_size大小
    if(ftruncate(dst_fd, file_size)){
        error(1, errno, "ftruncate");
    }

    off_t offset = 0;
    off_t length = 0;
    while(offset < file_size){
        if((file_size-offset)>=MMAP_SIZE){
            length = MMAP_SIZE;
        }else{
            length = file_size - offset;
        }

        void* src_addr = mmap(NULL, length, PROT_READ, MAP_SHARED, src_fd, offset);
        if(src_addr==MAP_FAILED){
            error(1, errno, "mmap src");
        }

        void* dst_addr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, offset);
        if(dst_addr==MAP_FAILED){
            error(1, errno, "mmap dst");
        }

        memcpy(dst_addr, src_addr, length);

        offset += length;

        if(munmap(src_addr, length)){
            error(1, errno, "munmap src");
        }

        if(munmap(dst_addr, length)){
            error(1, errno, "munmap dst");
        }

    }

    if(close(src_fd)){
        error(1, errno, "close %s", argv[1]);
    }

    if(close(dst_fd)){
        error(1, errno, "close %s", argv[2]);
    }
    return 0;
}