#define _XOPEN_SOURCE 600
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include<sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
struct sockaddr_in server;
static int sockfd=-1,listenfd=-1;
struct timeval tv;


void connect_request(){
    tv.tv_sec=2;
    tv.tv_usec=0;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd<0){
            perror("Error: socket");
            exit(1);
        }
        // printf("REached\n");
        if(connect(sockfd,(struct sockaddr*) &server,sizeof server)<0){
            perror("Error: connect");
            exit(2);
        }
        // printf("Reached\n");

        FILE *f;
        char name_requested[100],name_available[100];

        printf("What is the name of the file you want from the server(with extension)?\n");
        scanf("%s",name_requested);

        int a;
        a=send(sockfd,name_requested,strlen(name_requested),0);
	    //printf("%s\n",name_requested);
        if(a<strlen(name_requested)){
            perror("send()");
            exit(3);
        }

        //printf("Sent\n");
        int choice=1;
        setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&choice,sizeof(choice));

        a=recv(sockfd,name_available,sizeof(name_available),0);
	    //printf("%s\n",name_available);
        if(a<0){
            perror("Recv_error");
            exit(4);
        }
        //printf("Received\n");

        name_available[a]='\0';
        f=fopen(name_available,"ab");
        char recv_buffer[256];
        memset(recv_buffer,'\0',sizeof(recv_buffer));
        a=0;

        while((a=recv(sockfd,recv_buffer,sizeof recv_buffer,0))){
            printf("Bytes received %d\n",a);
            fwrite(recv_buffer,a,1,f);
        }
        fclose(f);
        close(sockfd);
        sockfd=-1;
        if(a < 0)
    {
        printf("\n Read Error \n");
    }

printf("File transfer successful\n");
}



int main(int argc, char** argv){
    memset(&server,0,sizeof(server));

    if(argc<2 || argc>3) {
        printf("Usage: ./client.out [host address] port\n");
        exit(0);
    }
    if(argc==2){
        printf("Assuming the server to be on the local host:\n");
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=inet_addr("127.0.0.1");
        server.sin_port=htons(atoi(argv[1]));

        connect_request();
    }
    else if(argc==3){
        printf("Address of the server: %s\nPort of server: %s\nIn process...\n",argv[1],argv[2]);
        server.sin_addr.s_addr=inet_addr(argv[1]);
        server.sin_family=AF_INET;
        server.sin_port=htons(atoi(argv[2]));

        connect_request();
    }





    return 0;
}
