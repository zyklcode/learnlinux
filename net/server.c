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

#include<sys/select.h>

int main(void){
    // 声明变量
    int serverfd, peerfd;
    if((serverfd=socket(AF_INET, SOCK_STREAM, 0))==-1){
        error(1, errno, "socket");
    }
    int optval = 0; 
    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))){
        error(1, errno, "setsockopt");
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    struct sockaddr_in peeraddrs[1024];
    for(int i=0;i<1024;i++){
        memset(&peeraddrs[i], 0, sizeof(peeraddrs[i]));
    }
    
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(8000);
    if(bind(serverfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))){
        error(1, errno, "bind");
    }
    if(listen(serverfd, 10)){
        error(1, errno, "listen");
    }else{
        printf("Server starts listening.\n");
    }

    char buffer_read[1024] = {0};
    char temp[2048] = {0};
    int nbytes = 0;
    int maxfd = 0;
    fd_set read_fds;
    FD_ZERO(&read_fds);

    FD_SET(serverfd, &read_fds);
    maxfd = maxfd > serverfd?maxfd:serverfd;

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
                if(FD_ISSET(serverfd, &read1_fds)){

                    
                    struct sockaddr_in peeraddr;
                    memset(&peeraddr, 0, sizeof(peeraddr));
                    socklen_t peersocklen = sizeof(peeraddr);

                    if((peerfd = accept(serverfd, (struct sockaddr*)&peeraddr, &peersocklen))==-1){
                        error(0, errno, "accept[%s:%d closed.]", inet_ntoa(peeraddr.sin_addr), \
                        ntohs(peeraddr.sin_port));
                    }else{
                        printf("%s:%d has connected, peerfd: %d.\n", inet_ntoa(peeraddr.sin_addr), \
                                    ntohs(peeraddr.sin_port), peerfd);
                        memcpy(peeraddrs+peerfd, &peeraddr, sizeof(peeraddr));
                        FD_SET(peerfd, &read_fds);
                        maxfd = maxfd > peerfd?maxfd:peerfd;
                    }
                }
                // if(FD_ISSET(STDIN_FILENO, &read1_fds)){
                //     fgets(buffer_send, sizeof(buffer_send), stdin);
                //     write(peerfd, buffer_send, strlen(buffer_send)+1);
                // }
                for(int i=0;i<(maxfd+1);i++){
                    peerfd = i;
                    if(FD_ISSET(peerfd, &read1_fds)&&(peerfd!=serverfd)){
                        nbytes = read(peerfd, buffer_read, sizeof(buffer_read));
                        if(nbytes == 0){
                            close(peerfd);
                            FD_CLR(peerfd, &read_fds);
                            error(0, errno, "fd %d read closed", peerfd);
                        }else if(nbytes == -1){
                            close(peerfd);
                            FD_CLR(peerfd, &read_fds);
                            error(0, errno, "fd %d read exception", peerfd);
                        }else{
                            printf("%s:%d [%d]: %s", inet_ntoa(peeraddrs[peerfd].sin_addr), \
                            ntohs(peeraddrs[peerfd].sin_port), peerfd, buffer_read);

                            buffer_read[strlen(buffer_read)] = 0;

                            for(int i=0;i<(maxfd+1);i++){
                                
                                if(i!=serverfd && i!= peerfd && FD_ISSET(i, &read_fds)){
                                    sprintf(temp, "%s:%d :%s", inet_ntoa(peeraddrs[i].sin_addr), \
                                        ntohs(peeraddrs[i].sin_port), buffer_read);
                                    nbytes = write(i, temp, strlen(temp)+1);
                                    if(nbytes == -1){
                                        close(i);
                                        FD_CLR(i, &read_fds);
                                        error(0, errno, "fd %d read exception", i);
                                    }
                                }
                            }
                        }
                    }
                }
                // if(FD_ISSET(peerfd, &read1_fds)){
                //     nbytes = read(peerfd, buffer_read, sizeof(buffer_read));
                //     if(nbytes == 0){
                //         goto end;
                //     }else if(nbytes == -1){
                //         close(peerfd);
                //         error(1, errno, "read");
                //     }else{
                //         printf("Client: %s", buffer_read);
                //     }
                // }
        }
        // nbytes = read(peerfd, buffer_read, sizeof(buffer_read));
        // if(nbytes==-1){
        //     close(peerfd);
        //     error(1, errno, "recv");
        // } else if(nbytes == 0){
        //     close(peerfd);
        //     break;
        // }else{
        //     printf("Client:%s",buffer_read); 
        // }
        // if((nbytes = write(peerfd, "Got\n\0", 5))==-1){
        //     close(peerfd);
        //     error(1, errno, "write");
        // }

    }
    close(peerfd);
    close(serverfd);
    
    return 0;
}