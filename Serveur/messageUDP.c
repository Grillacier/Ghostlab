#include "../includes/messageUDP.h"

int sendMess(char *port, char *message) {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    struct addrinfo *first_info;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    int r = getaddrinfo("235.1.2.4", port, &hints, &first_info);
    if (r == 0) {
        if (first_info != NULL) {
            struct sockaddr *saddr = first_info->ai_addr;
            sendto(sock, message, strlen(message), 0, saddr, sizeof(struct sockaddr));
        }
    }
    return 0;
}

int sendAllMessage(char *from, char *port, char *message) {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    struct addrinfo *first_info;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    int r = getaddrinfo("235.1.2.4", port, &hints, &first_info);
    if (r == 0) {
        if (first_info != NULL) {
            struct sockaddr *saddr = first_info->ai_addr;
            char buffer[250];
            char *req = "MESSA ";
            char *s = " ";
            char *end = "+++";
            memcpy(buffer, req, sizeof(char) * 6);
            memcpy(buffer + sizeof(char) * 6, from, sizeof(char) * 8);
            memcpy(buffer + sizeof(char) * 6, from, sizeof(char) * 8);
            memcpy(buffer + sizeof(char) * 14, s, sizeof(char) * 1);
            memcpy(buffer + sizeof(char) * 15, message, strlen(message));
            memcpy(buffer + sizeof(char) * 15 + strlen(message), end, sizeof(char) * 3);

            sendto(sock, buffer, sizeof(char) * 250, 0, saddr, (socklen_t)
            sizeof(struct sockaddr_in));
        }
    }
    return 0;
}

int sendMessage(char *from, char *ip, char *port, char *message) {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    struct addrinfo *first_info;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    int r = getaddrinfo(ip, port, &hints, &first_info);
    if (r == 0) {
        if (first_info != NULL) {
            struct sockaddr *saddr = first_info->ai_addr;
            char buffer[250];
            char *req = "MESSP ";
            char *s = " ";
            char *end = "+++";
            memcpy(buffer, req, sizeof(char) * 6);
            memcpy(buffer + sizeof(char) * 6, from, sizeof(char) * 8);
            memcpy(buffer + sizeof(char) * 6, from, sizeof(char) * 8);
            memcpy(buffer + sizeof(char) * 14, s, sizeof(char) * 1);
            memcpy(buffer + sizeof(char) * 15, message, strlen(message));
            memcpy(buffer + sizeof(char) * 15 + strlen(message), end, sizeof(char) * 3);

            sendto(sock, buffer, sizeof(char) * 250, 0, saddr, (socklen_t)
            sizeof(struct sockaddr_in));
            return 1;
        }
    }
    return 0;
}
