#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include "IO.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Enter ip\n");
        exit(1);
    }
    int s;
    struct sockaddr_in from;

    uint16_t port = 8080;
    in_addr_t ipv4 = inet_addr(argv[1]);
    from.sin_family = AF_INET;
    from.sin_addr.s_addr = ipv4;
    from.sin_port = htons(port);
    s = socket(AF_INET, SOCK_DGRAM, 0);

    int on = 1;

    double buf1;
    double buf2;
    if(bind(s, (struct sockaddr *)&from, sizeof(from)) < 0){
        perror("Connot bind");
        return 1;
    }
    for(;;){
        if(readDoubleData(s, buf1, from) < 0 || readDoubleData(s, buf2, from) < 0){
            return 1;
        }
        printf("buf1 = %f\n buf2 = %f\n", buf1, buf2);
        double res = buf1 + buf2;
        if(writeDoubleData(s, res, from) < 0){
            return 2;
        }

    }
    return 0;
}
