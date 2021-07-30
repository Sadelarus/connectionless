#pragma once
#include <sys/types.h>
#include <sys/socket.h>

int readDoubleData(int fd, double &num , struct sockaddr_in &from);

int writeDoubleData(int fd, double &num , const struct sockaddr_in &to);
