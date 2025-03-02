#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include<errno.h>
#include<error.h>

#include <string.h>

#include <unistd.h>

#include <stdio.h>

#include <sys/select.h>

int main(void){
    // 声明变量
    int fd;
    if((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
        error(1, errno, "socket");
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(8080);
    if(connect(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))){
        error(1, errno, "connect");
    }
    
    char buffer_send[1024] = {0};
    char buffer_read[1024] = {0};
    int nbytes = 0;
    int maxfd = 0;
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);
    maxfd = maxfd > fd?maxfd:fd;
    FD_SET(STDIN_FILENO, &read_fds);
    maxfd = maxfd > STDIN_FILENO?maxfd:STDIN_FILENO;
    while(1){
        fd_set read1_fds = read_fds;
        int event = select(maxfd+1, &read1_fds, NULL, NULL, NULL);
        switch (event)
        {
            case -1:
                error(1, errno, "select");
                break;
            case 0:
                printf("TIMEOUT\n");
                break;
            
            default:
                if(FD_ISSET(STDIN_FILENO, &read1_fds)){
                    fgets(buffer_send, sizeof(buffer_send), stdin);
                    write(fd, buffer_send, strlen(buffer_send)+1);
                }
                if(FD_ISSET(fd, &read1_fds)){
                    nbytes = read(fd, buffer_read, sizeof(buffer_read));
                    if(nbytes == 0){
                        goto end;
                    }else if(nbytes == -1){
                        close(fd);
                        error(1, errno, "read");
                    }else{
                        printf("%s", buffer_read);
                    }
                }
        }
        
        // printf("Client:");
        // if(fgets(buffer_send, sizeof(buffer_send), stdin)==NULL){
        //     close(fd);
        //     error(1, 0, "fgets");
        // }
        // if((nbytes = write(fd, buffer_send, strlen(buffer_send)+1))==-1){
        //     close(fd);
        //     error(1, errno, "write");
        // }
        // nbytes = read(fd, buffer_read, sizeof(buffer_read));
        // if(nbytes==-1){
        //     close(fd);
        //     error(1, errno, "recv");
        // } else if(nbytes == 0){
        //     close(fd);
        // }else{
        //     printf("Server:%s",buffer_read);
        // }
    }
end:
    close(fd);
    
    return 0;
}