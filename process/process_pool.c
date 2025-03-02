#include <errno.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <stdio.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>

#include <sys/epoll.h>

#include <sys/wait.h>

enum WORKSTATUS{
    FREE,
    BUSY,
};

typedef struct process_data_t{
    pid_t pid;
    int pipefd;
    enum WORKSTATUS status;
}process_data_t;

int sendFd(int pipefd, int peerfd){
    char buffer[4] = {0};
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    // 构建第二组成员
    struct iovec msg_iov;
    msg_iov.iov_base = buffer;
    msg_iov.iov_len = sizeof(buffer);
    msg.msg_iov = &msg_iov;
    msg.msg_iovlen = 1;
    // 第三组成员
    size_t len = CMSG_LEN(sizeof(peerfd));
    struct cmsghdr *cmsg = calloc(1, len);
    if(!cmsg){
        error(0, -1, "calloc[send fd error]");
        return -1;
    }
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    int *p = (int *)CMSG_DATA(cmsg);
    *p = peerfd;
    msg.msg_control = cmsg;
    // 与上面msg_iovlen不同，不是数组长度而是占用内存长度
    msg.msg_controllen = len;
    // 发送数据
    int ret = sendmsg(pipefd, &msg, 0);
    if(ret == -1){
        error(0, errno, "sendmsg");
    }
    printf("sendFd %d bytes.\n", ret);
    free(cmsg);
    return ret;

}


int recvFd(int pipefd, int* pfd){
    char buffer[4] = {0};
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    // 构建第二组成员
    struct iovec msg_iov;
    msg_iov.iov_base = buffer;
    msg_iov.iov_len = sizeof(buffer);
    msg.msg_iov = &msg_iov;
    msg.msg_iovlen = 1;
    // 第三组成员
    size_t len = CMSG_LEN(sizeof(int));
    struct cmsghdr *cmsg = calloc(1, len);
    if(!cmsg){
        error(0, -1, "calloc[send fd error]");
        return -1;
    }
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    
    msg.msg_control = cmsg;
    // 与上面msg_iovlen不同，不是数组长度而是占用内存长度
    msg.msg_controllen = len;
    // 发送数据
    int ret = recvmsg(pipefd, &msg, 0);
    *pfd = *(int *)CMSG_DATA(cmsg);
    free(cmsg);
    return ret;

}

int handleTask(int pipefd){
    printf("child start to handle task...\n");
    while(1){
        int peerfd;
        //当没有新连接，父进程不会调用sendFd函数
        printf("正在等待新的描述符到来\n");
        int ret = recvFd(pipefd, &peerfd);
        printf("已接收到新的任务，peerfd=%d\n", peerfd);
        // 执行发送大文件的操作
        write(peerfd, "Hello, client.\n\0", 16);
        // 发送完大文件后，关闭套接字
        close(peerfd);
        // 通知父进程工作完成，修改状态
        int on = 1;
        write(pipefd, &on, sizeof(on));
    }
    return 0;
}

int tcp_init(const char* sip, const char* sport){
    // 套接字
    int listenfd = 0;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
        error(1, errno, "socket");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(sip);
    int port = 0;
    sscanf(sport, "%d", &port);
    printf("%d\n", port);
    server_addr.sin_port = htons(port);

    int on = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))){
        error(0, errno, "setsockopt");
    }

    if(bind(listenfd, (const struct sockaddr*)&server_addr, sizeof(server_addr))){
        error(1, errno, "bind");
    }

    if(listen(listenfd, 64)){
        close(listenfd);
        error(1, errno, "listen");
    }
    return listenfd;
}

int make_child_process(process_data_t *pcbs, int processNum){
    for(int i=0;i<processNum;i++){
        int pipefds[2];
        if(socketpair(AF_LOCAL, SOL_SOCKET, 0, pipefds)){
           error(-1, errno, "socketpair");
        }
        pid_t pid = fork();
        if(pid == -1){
            error(-1, errno, "fork");
        }else if(pid == 0){
            // 子进程流程
            // 子进程关闭写
            close(pipefds[1]);
            handleTask(pipefds[0]);
            // 子进程退出
            exit(0);
        }else{
            // 父进程执行流
            // 保存子进程信息
            pcbs[i].pid = pid;
            pcbs[i].pipefd = pipefds[1];
            // 父进程关闭读
            close(pipefds[0]);
            pcbs[i].status = FREE;
        }
    }
    return 0;
}

int epoll_add_fd(int epollfd, int fd, struct epoll_event *pev){
    int ret;
    if((ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, pev))){
        error(0, errno, "epoll_ctl");
    }
    return ret;
}

int main(int argc, char *argv[]){
    // ./app ip port processNum
    // 判断命令行参数
    if(argc != 4){
        error(1, 0, "Usage: %s ip port processNum", argv[0]);
    }

    int processNum = 0;
    sscanf(argv[3], "%d", &processNum);

    process_data_t*pcbs = calloc(processNum, sizeof(process_data_t));
    // 创建N个进程池，并返回进程管理数据
    if(make_child_process(pcbs, processNum)){
        error(1, 0, "make_child_process");
    }

    int listenfd = tcp_init(argv[1], argv[2]);

    int epollfd = epoll_create1(0);
    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    if(epoll_add_fd(epollfd, listenfd, &ev)){
        close(listenfd);
        error(1, errno, "epoll_add_fd");
    }
    for(int i=0;i<processNum;i++){
        ev.data.fd = pcbs[i].pipefd;
        epoll_add_fd(epollfd, pcbs[i].pipefd, &ev);
    }
    struct epoll_event evs[1024];
    char buf_recv[4096] = {0};
    while(1){
        int nums = 0;
        if((nums = epoll_wait(epollfd, evs, 1024, -1))==-1){
            error(0, errno, "epoll_wait");
        }
        for(int i=0;i<nums;i++){
            int fd = evs[i].data.fd;
            int peerfd = 0;
            struct sockaddr_in peer_addr;
            socklen_t len = sizeof(peer_addr);
            if(fd == listenfd){
                if((peerfd = accept(listenfd, &peer_addr, &len))==-1){
                    continue;
                }else{
                    // 查找一个空闲子进程
                    for(int i=0;i<processNum;i++){
                        if(pcbs[i].status == FREE){
                            pcbs[i].status = BUSY;
                            // 发送套接字给对面
                            sendFd(pcbs[i].pipefd, peerfd);
                            break;
                        }
                    }
                }
            }else{
                int howmnay;
                read(fd, &howmnay, sizeof(howmnay));
                for(int i=0;i<processNum;i++){
                    if(fd == pcbs[i].pipefd){
                        pcbs[i].status = FREE;
                        printf("child %d finishs work, and changes state to FREE\n", pcbs->pid);
                        break;
                    }
                }
            }
        }
        
    }

    return 0;

}