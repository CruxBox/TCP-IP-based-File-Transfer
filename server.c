#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int args,char** arg){

    struct  sockaddr_in serv_ad;
    int connfd=0;
    int listenfd=0;
    //creating socket for listening:
    listenfd=socket(AF_INET, SOCK_STREAM,0);

    //setting up the serv_ad (server address struct) for using IPV4: 
    memset(&serv_ad,'0',sizeof(serv_ad));
    serv_ad.sin_family = AF_INET;
    serv_ad.sin_addr.s_addr=htons(INADDR_ANY);
    serv_ad.sin_port = htons(atoi(arg[1]));

    //binding the socket:
    bind(listenfd, (struct sockaddr*)&serv_ad, sizeof(serv_ad));
    if(listen(listenfd,5)==-1){
        printf("Cannot listen. Check error\n");
        exit(1);
    }
    
    //choosing file that server admin decides to send:
    FILE *file;
	if((file = fopen(arg[2], "rb"))==NULL){
		printf("Error opening file\n");
		exit(2);
	}
     // Find EOF
	fseek(file,0,SEEK_END);
  	unsigned long long fSize=ftell(file);
  	rewind(file);


    //Reading and sending process starts:
    while(1){
      printf("waiting...\n");
    connfd=accept(listenfd,(struct sockaddr*)NULL,NULL);
  	// allocate memory to contain the whole file in binary
  	char *buffer=(char*)malloc(sizeof(char)*fSize);

  	// copy the file into the buffer:
  	if(fread(buffer,1,fSize,file)!=fSize) {
  		printf("Buffer Fill Error\n");
  		exit(3);
  	}
  	fclose(file);
    //sending the data:
    write(connfd,buffer,fSize); 
    
    //closing current instance of socket
    close(connfd);
    sleep(1);
    }



    
    exit(0);
}