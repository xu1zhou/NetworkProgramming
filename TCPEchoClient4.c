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

    struct sockaddr_in Serveraddr;//this sockaddr will be cast to sockaddr when connect // sockaddr is Generics 泛型of socket,it's common use for vareious type of address 
    memset(&Serveraddr,0,sizeof(Serveraddr));
    Serveraddr.sin_family=AF_INET;
    
    int ret = inet_pton(AF_INET,ServerIP,&Serveraddr.sin_addr.s_addr);//convert ipaddr to network format
    if (ret<0)
        printf("convert ip address failed");
    

    Serveraddr.sin_port=htons(port);


    if(connect(sock,(struct sockaddr *)&Serveraddr,sizeof(Serveraddr)) < 0)// connect will return after 3-handshake finish
        printf("connect failed");

    size_t echoStringLen = strlen(echoString);


    ssize_t numBytes = send(sock,echoString,echoStringLen,0); // send will return once data is copy to kernel buffer, not real sent to server.
    if (numBytes < 0)
        printf("send() failed");
    else if (numBytes != echoStringLen)
        printf("send unexpected num of bytes");


    unsigned int totalBytesString = 0;
    fputs("recv:",stdout);
    
    while(totalBytesString < numBytes){
        char Buffer[20];
        numBytes=recv(sock,Buffer,19,0);
        if (numBytes < 0)
            printf("recv error");
        else if (numBytes == 0)
            print("connection closed permaturely");
        else
            totalBytesString += numBytes;
            fputs(Buffer,stdout);
        }
    fputc('\0',stdout);

}
