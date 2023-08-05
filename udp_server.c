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
    int optval=1;
    int sockfd,connfd=0;
    char sendbuf[4096]= {"success"},revbuf[4096]= {};
    char buf[9999];
    

    struct sockaddr_in server_addr,client_addr;
    socklen_t len=sizeof(struct sockaddr_in*);
        
    sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))< 0)
    {
        printf("setsockopt bind error!\n");
        exit(0);
    }

    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("bind failed!\n");
        exit(0);
    }
/*
    if(listen(sockfd,SOMAXCONN)<0)
    {
        printf("listen failed!\n");
        exit(0);
    }
*/
   
////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    while(1)
    {
    recvfrom(sockfd,revbuf,sizeof(revbuf),0,(struct sockaddr*) &client_addr,&len);

    printf("revbuf = %s\n",revbuf);
    printf("%s %d %s", "client_addr.sin_port =",ntohs(client_addr.sin_port),"\n");
    printf("%s %s %s", "client_addr.sin_addr.s_addr =",inet_ntoa(client_addr.sin_addr),"\n");

    strcat((char*)revbuf," --echo--");
    
    sendto(sockfd,&revbuf,sizeof(revbuf),0,(struct sockaddr*)&client_addr,sizeof(client_addr));

    //close(sockfd);

    //return 0;
    }
    close(sockfd);

    return 0;
}
