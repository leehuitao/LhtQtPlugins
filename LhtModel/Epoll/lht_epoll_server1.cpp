#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#define MESSAGE_LEN 1024
#define MAX_EVENT 20
#define TIME_OUT 500
int main(int argc , char* argv[]){
        int socket_fd = -1;
	int accept_fd,acceptlen;
	int epoll_fd;
	epoll_event ev,events[MAX_EVENT];
	int event_number;
	char buffer[MESSAGE_LEN];
        socket_fd = socket(AF_INET,SOCK_STREAM,0);
        if(socket_fd == -1 ){
                std::cout<<"create socket error"<<std::endl;
                exit(-1);
        }
	int flags = fcntl(socket_fd ,F_GETFL,0);
        fcntl(socket_fd,F_SETFL,flags | O_NONBLOCK);

	int on = 1;
        int ret = setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int));
        if(ret == -1){
                std::cout<<"faild to set socket opt"<<std::endl;
        }
	struct sockaddr_in localaddr,remoteaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = 8111;
	localaddr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(socket_fd,(struct sockaddr *)&localaddr,sizeof(sockaddr_in));
	if(ret == -1){
		std::cout<<"faild to bind socket "<<std::endl;
		exit(-1);
	}   
	ret = listen(socket_fd,10);
       if(ret == -1){
                std::cout<<"faild to listen socket "<<std::endl;
                exit(-1);
        }
	std::cout<<"init success "<<std::endl;
	epoll_fd = epoll_create(256);
	ev.events = EPOLLIN;
	ev.data.fd = socket_fd;
	epoll_ctl(epoll_fd,EPOLL_CTL_ADD,socket_fd,&ev);
	
	for(;;){
		event_number = epoll_wait(epoll_fd,events,MAX_EVENT,TIME_OUT);
		for(int i = 0 ; i < event_number; i ++){
			if(events[i].data.fd == socket_fd){
				acceptlen = sizeof(sockaddr);
                		accept_fd = accept(socket_fd,(sockaddr*)&remoteaddr,(socklen_t*)&acceptlen);
                		std::cout<<"new socket"<<std::endl;		
				int flags = fcntl(accept_fd ,F_GETFL,0);
				fcntl(accept_fd,F_SETFL,flags | O_NONBLOCK);
				ev.events = EPOLLIN | EPOLLET;
        			ev.data.fd = accept_fd;
			        epoll_ctl(epoll_fd,EPOLL_CTL_ADD,accept_fd,&ev);

			}else if(events[i].events & EPOLLIN){
	//			do{
					std::cout<<"-00-------------------------"<<std::endl;
					memset(&buffer,0,MESSAGE_LEN);
					ret = recv(events[i].data.fd,(void*)buffer,MESSAGE_LEN,0);
                	        	if(ret == 0){
        	                        	close(events[i].data.fd);
	                        	}
					if(ret == MESSAGE_LEN){
						std::cout<<"tai duo le  : "<<std::endl;
					}
					if(ret < 0 ){
						std::cout<<"error : "<<std::endl;
					}
	//			}while(ret < -1 && errno == EINTR);
					std::cout<<"recv : "<<buffer<<std::endl;
        	                	send(events[i].data.fd,(void *)buffer,MESSAGE_LEN,0);
	
			}
			std::cout<<"events[i].events: "<<events[i].events<<std::endl;
		}

	}
	close(socket_fd);
	return 0;
}

