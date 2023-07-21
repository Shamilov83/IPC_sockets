#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main(int argc,char *argv[])
{
    struct sockaddr_in user;
    int sockfd;
    char sendbuf[100],revbuf[100];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("socket failed!\n");
        exit(0);
    }
    user.sin_family = AF_INET;
    user.sin_port = htons(8001);
    user.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ( connect(sockfd, (struct sockaddr*) (&user), sizeof(user)) < 0)
    {
        perror("connect failed!\n");
        exit(0);
    }
    while(~scanf("%s",sendbuf))
    {
        write(sockfd,sendbuf,sizeof(sendbuf));
        read(sockfd,revbuf,sizeof(revbuf));
        printf("client revmsg:%s\n",revbuf);
        memset(sendbuf,0,sizeof(sendbuf));
        memset(sendbuf,0,sizeof(revbuf));
    }
    close(sockfd);
    return 0;
}