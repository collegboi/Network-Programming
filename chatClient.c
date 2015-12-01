#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "unp.h" 
#define SERV_TCP_PORT 5035
int main(int argc,char*argv[])
{
	int sockfd;
	struct sockaddr_in serv_addr;
	char buffer[4096];
	char readBuff[4096];
	struct sockaddr_in servaddr;

	if(argc != 3)
		err_quit("usage:a.out <IPaddress>");

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));

	printf("\nPTON...");
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	printf("\nReady for sending...");
	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) <0)
		err_sys("connect error");

	//sockfd=socket(AF_INET,SOCK_STREAM,0);
	//serv_addr.sin_family=AF_INET;
	//serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	//serv_addr.sin_port=htons(SERV_TCP_PORT);

	//we connect to the server
	//printf("\nReady for sending...");
	//connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	while(1) {

		printf("\nEnter the message to send\n");
		printf("\nClient: ");

		//write out
		fgets(buffer,4096,stdin);
		write(sockfd,buffer,4096);

		//read in
		printf("\nWaiting for reponse from server\n");
		read(sockfd,readBuff,4096);
		printf("\nServer message:%s",readBuff);

//		printf("Serverecho:%s",buffer);
//		printf("\n");
	}

	close(sockfd);
	return 0;
}