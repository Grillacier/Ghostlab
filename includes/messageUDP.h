#ifndef MESSAGEUDP_H
#define MESSAGEUDP_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

int sendMess(char *port, char *message);
int sendAllMessage(char *from, char *port, char *message);
int sendMessage(char *from, char *ip, char *port, char *message);

#endif //MESSAGEUDP_H
