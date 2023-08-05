#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <inttypes.h>

int sockfd;
char sendbuf[4096],revbuf[4096];
char msg[] = "Hello World";
char buf[9999];

struct sockaddr_in server_addr;

int main(int argc,char *argv[])
{     
   	
    	if((sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1)
    	{
    	    printf("socket failed!\n");
    	    exit(0);
    	}
    
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(4001);
    	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	
    	if((sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
    	{
    	perror("error sendto");
    	} else {
    	printf("sendto ok\n");
    	}
    	
    	
 
    	while(1){
    	 	if((recvfrom(sockfd,&revbuf,sizeof(revbuf),0,(struct sockaddr*)NULL,NULL)) < 0){
    	 	printf("error revmsg");
    	 	}
    	 	else{
    	 	printf("revbuf = %s\n",revbuf);
    		printf("server_addr.sin_port = %d\n",ntohs(server_addr.sin_port));
    		printf("server_addr.sin_addr.s_addr = %s\n",inet_ntoa(server_addr.sin_addr));
    	 	}
    	 	
    	}	
    	

    	

    	close(sockfd);
    	return 0;
}
