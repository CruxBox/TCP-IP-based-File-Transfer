#define _XOPEN_SOURCE 600
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
struct timeval tv;


int main(int argc,char** argv){
        struct sockaddr_in server,client;
        int sockfd=0,connfd=0;
	int size=sizeof(struct sockaddr);
        sockfd=socket(AF_INET,SOCK_STREAM,0);

        memset(&server,'0',sizeof(server));

        server.sin_addr.s_addr=INADDR_ANY;
        server.sin_family=AF_INET;
        server.sin_port=htons(atoi(argv[1]));
	    printf("Enter port number %d in client side\n",ntohs(server.sin_port));
 
        const int optionval = 1;
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT | SO_SNDTIMEO, &optionval, sizeof(optionval));

        bind(sockfd,(struct sockaddr*)&server,sizeof server);
        
        // printf("Reached after bind\n");
        if(listen(sockfd,10)<0){
        perror("listen()");
        exit(1);
        }
        // printf("Reached after listen\n");
        FILE *log;
        log=fopen("logs.txt","ra");
        
        while(1){
            connfd=accept(sockfd,(struct sockaddr*)&client,&size);

        char name_requested[100];
        int a=0;
        a=recv(connfd,name_requested,sizeof(name_requested),0);
        if(a<0){
            perror("recv()->name_requested");
            exit(1);
        }
        name_requested[a]='\0';

        
        FILE* f;
        char* buffer=(char*)malloc(sizeof(char)*256);
        if(f=fopen(name_requested,"rb")){
            send(connfd,name_requested,strlen(name_requested),0);
            int p=0;
            //send requested file
            while(!feof(f)){
                p=fread(buffer,1,sizeof(buffer),f);
                printf("Bytes read: %d\t",p);
                p=send(connfd,buffer,p,0);
                printf("Bytes sent: %d\n",p);
                if(p<0){
                    perror("Not sent any bytes");
                    exit(5);
                }
            }
            fclose(f);
            close(connfd);
            printf("Sending process done\n");

        }
        else{
            //send log.txt file
            send(connfd,"logs.txt",8,0);
            printf("logs.txt\n");
            int p=0;
            while(!feof(log)){
                p=fread(buffer,1,sizeof(buffer),log);
                send(connfd,buffer,p,0);
                
            }

            close(connfd);

        }
            
}
 return 0;
 }
