#include <error.h>
#include <errno.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/socket.h>

#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#include<sys/epoll.h>

#include<stdlib.h>

#define MAX_EVENTS 512

typedef enum status{
    FREE,
    BUSY
}status_t;

typedef struct process_control_block{
    pid_t pid;
    int pipefd;
    status_t status;

}process_control_block;


int send_fd_to_child_process(int pipefd, int peerfd){
    write(pipefd, &peerfd, sizeof(int));
    return 0;
}

int recv_fd_from_parent_process(int pipefd){
    int fd = 0;
    read(pipefd, &fd, sizeof(int));
    return fd;
}

int tcp_init(const char* ip, const char* sport){
    int listenfd = 0;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
        error(1, errno, "socket");
    }
    int on = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int))){
        error(1, errno, "setsocketopt");
    }
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(ip);
    int port = 0;
    sscanf(sport, "%d", &port);
    servAddr.sin_port = htons(port);

    if(bind(listenfd, (struct sockaddr*)&servAddr, sizeof(servAddr))){
        error(1, errno, "bind");
    }

    if(listen(listenfd, 100)){
        error(1, errno, "listen");
    }
    return listenfd;
}


void epoll_add(int epollfd, int otherfd, struct epoll_event* event_p){
    (*event_p).data.fd = otherfd;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, otherfd, event_p)){
        error(1, errno, "epoll");
    }
}

void handle_task(int pipefd){
    printf("Child Process: Starting to work...\n");
    int peerfd = 0;
    int nums = 0;
    while(1){
        peerfd = recv_fd_from_parent_process(pipefd);
        nums++;
        printf("Child Process: Starting to handle No.%d task...\n", nums);
        // handle the task
        sleep(5);
        printf("Child Process: complete No.%d task...\n", nums);
        close(peerfd);
        // tell parent process
        int success = 0;
        write(pipefd, &success, sizeof(success));
    }
}

void make_child_process(int processNum, process_control_block pcbs[]){
    for(int i=0;i<processNum;i++){
        int sv[2];
        if(socketpair(AF_LOCAL, SOCK_STREAM, 0, sv)){
            error(1, errno, "socketpair");
        }
        pid_t pid = fork();
        if(pid < 0){
            error(1, errno, "fork");
        }else if(pid == 0){
            // child process
            // close write
            close(sv[1]);
            handle_task(sv[0]);
            exit(0);
        }else{
            // parent process
            close(sv[0]);
            pcbs[i].pid = pid;
            pcbs[i].pipefd = sv[1];
            pcbs[i].status = FREE;
        }
    }
}


int main(int argc, char* argv[]){
    if(argc!=4){
        error(1, 0, "Usage: %s ip port nums", argv[0]);
    }

    int processNums = 0;
    sscanf(argv[3], "%d", &processNums);
    // get the nums
    // create processes
    process_control_block pcbs[processNums];
    make_child_process(processNums, pcbs);

    // create the socket
    int listenfd = tcp_init(argv[1], argv[2]);

    int epollfd = 0;
    if((epollfd = epoll_create1(0))==-1){
        error(1, errno, "epoll_create1");
    }
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = listenfd;
    epoll_add(epollfd, listenfd, &event);
    for(int i=0;i<processNums;i++){
        epoll_add(epollfd, pcbs[i].pipefd, &event);
    }
    int nfds = 0;
    struct epoll_event events[MAX_EVENTS];
    while(1){
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if(nfds == -1){
            error(1, errno, "epoll_wait");
        }
        for(int i=0;i<nfds;i++){
            int fd = events[i].data.fd;
            if(fd == listenfd){
                struct sockaddr_in peerAddr;
                socklen_t socklen = 0;
                int peerfd = 0;
                if((peerfd = accept(fd, (struct sockaddr*)&peerAddr, &socklen))==-1){
                    error(1, errno, "accept");
                } 
                
                for(int i=0;i<processNums;i++){
                    if(pcbs[i].status == FREE){
                        send_fd_to_child_process(pcbs[i].pipefd, peerfd);
                        pcbs[i].status = BUSY;
                        break;
                    }
                }
            }else{
                int status = 0;
                read(fd, &status, sizeof(status));
                for(int i=0;i<processNums;i++){
                    if(fd == pcbs[i].pipefd){
                        pcbs[i].status = FREE;
                        printf("child %d finishs working, and changes state to FREE\n", pcbs->pid);
                        break;
                    }
                }
            }
        }
    }

    return 0;
}