#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// #include <Practical.h>

int main(int argc, char* argv[]){
    if (argc < 3 || argc > 4){
        DieWithUserMessage("parameter(s)");
    }
    
    
    char* ServerIP=argv[1];
    char* echoString=argv[2];

    
    in_port_t port= (argc==4) ? atoi(argv[3]) : 7; 
    
    
    int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);// create socket, 4 tuple has not set 
    if (sock>0){
        printf("create socket failed");
    }

    struct sockaddr_in Serveraddr;//this sockaddr will be cast to sockaddr when connect TODO difference between sockaddr_in sockaddr
    memset(&Serveraddr,0,sizeof(Serveraddr));
    Serveraddr.sin_family=AF_INET;
    
    int ret = inet_pton(AF_INET,ServerIP,&Serveraddr.sin_addr.s_addr);//convert ipaddr to network format
    if (ret<0)
        printf("convert ip address failed");
    

    Serveraddr.sin_port=htons(port);


    if(connect(sock,(struct sockaddr *)&Serveraddr,sizeof(Serveraddr))<0)
        printf("connect failed");
}
