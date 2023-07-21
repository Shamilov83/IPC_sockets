#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main(int argc,char * argv[])
{
    pid_t pid;
    int listenfd,connfd=0;
    char sendbuf[100]= {"success"},revbuf[100]= {};
    struct sockaddr_in ser,clt;
    socklen_t len=sizeof(clt);
    
    listenfd=socket(AF_INET,SOCK_STREAM,0);
   
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8001);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
    int optval=1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))< 0)
    {
        printf("setsockopt bind error!\n");
        exit(0);
    }
    if(bind(listenfd,(struct sockaddr*)&ser,sizeof(ser))<0)
    {
        printf("bind failed!\n");
        exit(0);
    }
    if(listen(listenfd,SOMAXCONN)<0)
    {
        printf("listen failed!\n");
        exit(0);
    }
    while(1)
    {
        connfd=accept(listenfd,(struct sockaddr*)&clt,(socklen_t *)&len);
        pid=fork();
        if(pid==0)
        {
            close(listenfd);  	//закончить прослушивание
            printf("child process running\n");
            while(1)		//считать данные
            {
                int ret=read(connfd,revbuf,sizeof(revbuf));
                if(ret<0)
                {
                    printf("read failed!\n");
                    exit(0);
                }
                else if(ret==0)
                {
                    printf("client closed\n");
                    exit(0);
                }
                printf("server revmsg:%s\n",revbuf);
                write(connfd,sendbuf,sizeof(sendbuf));
                memset(revbuf,0,sizeof(revbuf));
            }
        }
        else if(pid>0)
        {
            close(connfd);   //разорвать соединение с клиентом
        }
        else
        {
            printf("create failed!\n");
            close(connfd);
            close(listenfd);
            exit(0);
        }
    }
    if(pid==0)
    {
        close(connfd);
    }
    else
    {
        close(listenfd);
    }
    return 0;
}
