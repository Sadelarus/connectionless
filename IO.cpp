#include "IO.h"
#include <cstdio>
#include <cstring>
#include <poll.h>
#include <stdint.h>
#include <arpa/inet.h>

int readDoubleData(int fd, double &num , struct sockaddr_in &from){
    struct pollfd fds;
    fds.fd = fd;
    ssize_t sizeB=0;
    uint8_t buf[sizeof(double)];
    size_t offset = 0;
    for(;;){
        fds.events = POLLIN | POLLRDHUP | POLLHUP | POLLERR;
        fds.revents = 0;
        int res = poll(&fds, 1, -1);
        if(res<0){
            return -1;
        }
        if(res == 0){
            continue;
        }
        if(fds.revents & POLLIN) {
            int len = sizeof(from);
            ssize_t r = recvfrom(fds.fd, buf+offset, sizeof(buf)-offset, 0, (struct sockaddr *)&from, (socklen_t*)&len);

            if (r > 0) {
                sizeB+=r;
                offset+=r;
                if(sizeB >= sizeof(double)) {
                    break;
                } else if(r < 0){
                    printf("Error read(%d)\n", fd);
                    return -1;
                } else if(r == 0){
                    printf("Warning read(%d): 0\n", fd);
                    continue;
                }
            }
            if(fds.revents & POLLRDHUP){
                printf("Error: unable to read from %d due to POLLRDHUP", fds.fd);
            } else if(fds.revents &  POLLHUP){
                printf("Error: unable to read from %d due to POLLHUP", fds.fd);
            } else if(fds.revents &  POLLERR){
                printf("Error: unable to read from %d due to POLLERR", fds.fd);
            }
            return -1;
        }
    }
    double v;
    memcpy(&v, buf, sizeof(buf));
    num = v;
    return sizeB;
}

int writeDoubleData(int fd, double &num , const struct sockaddr_in &to){
    struct pollfd fds;
    fds.fd = fd;
    ssize_t sizeB=0;
    uint8_t *buf = (uint8_t *)&num;
    size_t offset = 0;
    for(;;){
        fds.events = POLLOUT | POLLRDHUP | POLLHUP | POLLERR;
        fds.revents = 0;
        int res = poll(&fds, 1, -1);
        if(res < 0){
            return -1;
        }
        if(res == 0){
            continue;
        }
        if(fds.revents & POLLOUT) {
            socklen_t len = (socklen_t)sizeof(to);
            ssize_t r = sendto(fds.fd, buf+offset, sizeof(double)-offset, 0, (struct sockaddr *)&to, len);

            if (r > 0) {
                sizeB+=r;
                offset+=r;
                if(sizeB >= sizeof(double)) {
                    break;
                } else if(r < 0){
                    printf("Error write(%d)\n", fd);
                    return -1;
                } else if(r == 0){
                    printf("Warning write(%d): 0\n", fd);
                    continue;
                }
            }
            if(fds.revents & POLLRDHUP){
                printf("Error: unable to write to %d due to POLLRDHUP", fds.fd);
            } else if(fds.revents &  POLLHUP){
                printf("Error: unable to write to %d due to POLLHUP", fds.fd);
            } else if(fds.revents &  POLLERR){
                printf("Error: unable to write to %d due to POLLERR", fds.fd);
            }
            return -1;
        }
    }
    double v;
    memcpy(&v, buf, sizeof(buf));
    num = v;
    return sizeB;
}
