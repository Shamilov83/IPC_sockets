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
char msg[] = "raw_client";
char buf[9999];

struct sockaddr_in server_addr;
socklen_t len=sizeof(struct sockaddr_in*);

struct udphdr {
uint16_t uh_sport;
uint16_t uh_dport;
uint16_t uh_ulen;
uint16_t uh_sum;
} udph;

char *ptr_data = (buf + sizeof(struct udphdr));
char *ptr_hdr = buf;

int main(int argc,char *argv[])
{
	//UDP header
	udph.uh_sport = htons(4002);
	udph.uh_dport = htons(4001);
	udph.uh_ulen = sizeof(buf);
	udph.uh_sum = 0;
        
        strcpy(ptr_hdr,(char*)&udph);
   	strcpy(ptr_data,msg);
   	
    	if((sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_UDP)) == -1)
    	{
    	    printf("socket failed!\n");
    	    exit(0);
    	}
    
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(4001);
    	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    	sendto(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
    	
    	while(1){
    	 if((recvfrom(sockfd,&revbuf,sizeof(revbuf),0,(struct sockaddr*)NULL,NULL)) < 0){;
 
    	 }
	if(server_addr.sin_port == udph.uh_dport){

    	printf("revbuf = %s\n",revbuf+28);
    	printf("%s %d %s", "server_addr.sin_port =",ntohs(server_addr.sin_port),"\n");
    	printf("%s %s %s", "server_addr.sin_addr.s_addr =",inet_ntoa(server_addr.sin_addr),"\n");
    	
     	}
	else {

	printf("no server response\n");
	
	close(sockfd);
    	return 0;	
    	}
    	
    }
    	

    	close(sockfd);
    	return 0;
}
