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
}
