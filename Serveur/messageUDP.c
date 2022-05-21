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

int sendAllMessage(char * from , char*port,char *message){
	int sock=socket(PF_INET,SOCK_DGRAM,0);
	struct addrinfo *first_info;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype=SOCK_DGRAM;
	int r=getaddrinfo("235.235.235.235",port,&hints,&first_info);
		if(r==0){
			if(first_info!=NULL){
				struct sockaddr *saddr=first_info->ai_addr;
				char buffer[250];
				char *req = "MESSA ";
				char *s = " ";
				char *end = "+++";
				memcpy(buffer,req,sizeof(char)*6);
memcpy(buffer+sizeof(char)*6,from,sizeof(char)*8);							memcpy(buffer+sizeof(char)*6,from,sizeof(char)*8);
memcpy(buffer+sizeof(char)*14,s,sizeof(char)*1);
memcpy(buffer+sizeof(char)*15,message,strlen(message));
memcpy(buffer+sizeof(char)*15+strlen(message),end,sizeof(char)*3);

				
				
				sendto(sock,buffer,sizeof(char)*250,0,saddr,(socklen_t)sizeof(struct sockaddr_in));
						
					}
		}
	return 0;

}

int sendMessage(char *from,char * ip, char *port,char* message) {
	int sock=socket(PF_INET,SOCK_DGRAM,0);
	struct addrinfo *first_info;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype=SOCK_DGRAM;
	int r=getaddrinfo(ip,port,&hints,&first_info);
		if(r==0){
			if(first_info!=NULL){
				struct sockaddr *saddr=first_info->ai_addr;
				char buffer[250];
				char *req = "MESSP ";
				char *s = " ";
				char *end = "+++";
				memcpy(buffer,req,sizeof(char)*6);
memcpy(buffer+sizeof(char)*6,from,sizeof(char)*8);							memcpy(buffer+sizeof(char)*6,from,sizeof(char)*8);
memcpy(buffer+sizeof(char)*14,s,sizeof(char)*1);
memcpy(buffer+sizeof(char)*15,message,strlen(message));
memcpy(buffer+sizeof(char)*15+strlen(message),end,sizeof(char)*3);

				
				
				sendto(sock,buffer,sizeof(char)*250,0,saddr,(socklen_t)sizeof(struct sockaddr_in));
					return 1;	
					}
		}
	return 0;
}

/*int main(){
	sendMessage("popolala","localhost","4242","Je tenvoie ce message");

} */
