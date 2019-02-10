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
    int sockfd=0;
    struct sockaddr_in serv_ad;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    serv_ad.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_ad.sin_family=AF_INET;
    serv_ad.sin_port=htons(atoi(arg[1]));

    if(connect(sockfd,(struct sockaddr *)&serv_ad,sizeof(serv_ad))<0) 
    {
            printf("Cannot connect\n");
        exit(1);
    }
    FILE *file;
    char filename[100];
    printf("Enter name of file to be saved: ");
    scanf("%s",filename);
    file=fopen(filename,"ab");
    char recvBuff[2147483646];
	memset(recvBuff,'0',sizeof(recvBuff));
    unsigned long long bytesReceived=0;
    while((bytesReceived = read(sockfd, recvBuff, sizeof(recvBuff))))
    {
        printf("Bytes received %lld\n",bytesReceived);    

        fwrite(recvBuff, 1,bytesReceived,file);

    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

printf("File transfer successful\n");
    

return 0;
        }
