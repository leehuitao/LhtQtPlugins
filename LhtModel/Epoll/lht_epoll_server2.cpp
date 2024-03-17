/* 实现功能：通过epoll, 处理多个socket
 * 监听一个端口,监听到有链接时,添加到epoll_event
 * xs
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h> 

#define MYPORT 12345
 
//最多处理的connect
#define MAX_EVENTS 500
 
//当前的连接数
int currentClient = 0; 
 
//数据接受 buf
#define REVLEN 10
char recvBuf[REVLEN];
 
 
//epoll描述符
int epollfd;
//事件数组
struct epoll_event eventList[MAX_EVENTS];
 
void AcceptConn(int srvfd);
void RecvData(int fd);
 
int main()
{
    int i, ret, sinSize;
    int recvLen = 0;
    fd_set readfds, writefds;
    int sockListen, sockSvr, sockMax;
    int timeout;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    
    //socket
    if((sockListen=socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        return -1;
    }
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family  =  AF_INET;
    server_addr.sin_port = htons(MYPORT);
    server_addr.sin_addr.s_addr  =  htonl(INADDR_ANY); 
    
    //bind
    if(bind(sockListen, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("bind error\n");
        return -1;
    }
    
    //listen
    if(listen(sockListen, 5) < 0)
    {
        printf("listen error\n");
        return -1;
    }
    
    // epoll 初始化
    epollfd = epoll_create(MAX_EVENTS);
    struct epoll_event event;
    event.events = EPOLLIN|EPOLLET;
    event.data.fd = sockListen;
    
    //add Event
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, sockListen, &event) < 0)
    {
        printf("epoll add fail : fd = %d\n", sockListen);
        return -1;
    }
    
    //epoll
    while(1)
    {
        timeout=3000;                
        //epoll_wait
        //参数释义：

        //events：用来从内核得到事件的集合
        //maxevent：用于告诉内核这个event有多大，这个maxevent不能大于创建句柄时的size
        //timeout：超时时间
        //··· -1：阻塞
        //··· 0：立即返回
        //···>0：指定微秒
        //成功返回有多少个文件描述符准备就绪，时间到返回0，出错返回-1.
        int ret = epoll_wait(epollfd, eventList, MAX_EVENTS, timeout);
        
        if(ret < 0)
        {
            printf("epoll error\n");
            break;
        }
        else if(ret == 0)
        {
            printf("timeout ...\n");
            continue;
        }
        
        //直接获取了事件数量,给出了活动的流,这里是和poll区别的关键
        int i = 0;
        for(i=0; i<ret; i++)
        {
            //错误退出
            if ((eventList[i].events & EPOLLERR) ||
                (eventList[i].events & EPOLLHUP) ||
                !(eventList[i].events & EPOLLIN))
            {
              printf ( "epoll error\n");
              close (eventList[i].data.fd);
              return -1;
            }
            
            if (eventList[i].data.fd == sockListen)
            {
                AcceptConn(sockListen);
        
            }else{
                RecvData(eventList[i].data.fd);
            }
        }
    }
    
    close(epollfd);
    close(sockListen);
    
 
    return 0;
}
 
/**************************************************
函数名：AcceptConn
功能：接受客户端的链接
参数：srvfd：监听SOCKET
***************************************************/
void AcceptConn(int srvfd)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(struct sockaddr_in);
    bzero(&sin, len);
 
    int confd = accept(srvfd, (struct sockaddr*)&sin, &len);
 
    if (confd < 0)
    {
       printf("bad accept\n");
       return;
    }else
    {
        printf("Accept Connection: %d", confd);
    }
    //将新建立的连接添加到EPOLL的监听中
    struct epoll_event event;
    event.data.fd = confd;
    event.events =  EPOLLIN|EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, confd, &event);
}
 
//读取数据
void RecvData(int fd)
{
    int ret;
    int recvLen = 0;
    
    memset(recvBuf, 0, REVLEN);
    printf("RecvData function\n");
    
    if(recvLen != REVLEN)
    {
        while(1)
        {
            //recv数据
            ret = recv(fd, (char *)recvBuf+recvLen, REVLEN-recvLen, 0);
            if(ret == 0)
            {
                recvLen = 0;
                break;
            }
            else if(ret < 0)
            {
                recvLen = 0;
                break;
            }
            //数据接受正常
            recvLen = recvLen+ret;
            if(recvLen<REVLEN)
            {
                continue;
            }
            else
            {
                //数据接受完毕
                printf("buf = %s\n",  recvBuf);
                recvLen = 0;
                break;
            }
        }
    }
 
    printf("data is %s", recvBuf);
}