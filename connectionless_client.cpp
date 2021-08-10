#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "IO.h"


int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("Usage: %s ip_addr\n", argv[0]);
        exit(1);
    }
    struct sockaddr_in server;
    uint16_t port = 8080;
    int s;
    double a1 = 2;
    double a2 = 3;
    double res = 10;

    in_addr_t ipv4 = inet_addr(argv[1]);
    bzero((char*)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = ipv4;
    s = socket(AF_INET,SOCK_DGRAM,0);
    if(s<0){
        perror("socket");
        exit(3);
    }
    printf("WORK IN PROCESS\n");
    /*if(bind(s,(struct sockaddr *)&server,sizeof(server))<0){
        perror("bind");
        exit(4);
    }*/
    int len = (socklen_t)sizeof(server);
    if(writeDoubleData(s, a2, server) < 0 || writeDoubleData(s, a1, server) < 0){
        return 2;
    }
    if(readDoubleData(s, res, server) < 0){
        return 1;
    }
    close(s);
    printf("%f + %f = %f\n", a1, a2, res);
}
