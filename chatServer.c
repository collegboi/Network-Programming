#include<stdio.h>
#include<netinet/in.h>
#include<netdb.h>
#include "unp.h"
#define SERV_TCP_PORT 5035
int main(int argc,char**argv)
{
	int sockfd,newsockfd,clength, listenfd, connfd, n;

	//struct sockaddr_in serv_addr,cli_addr;
	char buffer[4096];
	char writebuff[4096];;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	int counter = 0;

	if(argc != 2) //verifies number of command-line args; two in this instance
		err_quit("usage: <Program Name> <Port No.>");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0); //create socket

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family 	=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port	=htons(atoi(argv[1]));

	/*
listenfd = Socket(AF_INET, SOCK_STREAM, 0); //create socket

	sockfd=socket(AF_INET,SOCK_STREAM,0);
 	serv_addr.sin_family=AF_INET;
 	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(SERV_TCP_PORT);
*/
	printf("\nStart");
	Bind(listenfd, (SA *) &servaddr,sizeof(servaddr));

	printf("\nListening...");
	Listen(listenfd, LISTENQ);

	/*
printf("\nStart");
	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	printf("\nListening...");
	printf("\n");
	listen(sockfd,5);
*/

	//then we accept the connection from client
	//clength=sizeof(cli_addr);
	//newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);

	len = sizeof(cliaddr);
	connfd = Accept(listenfd, (SA *) &cliaddr, &len);

	printf("\nAccepted\n");

	//printf("\r\nClient Addr %lu \r\n", &cliaddr.sin_addr);
	//printf("Client Port %hu \r\n", cliaddr.sin_port);

	//printf("connection from %s, port %d\n",
	//		Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
	//		ntohs(cliaddr.sin_port) );
	while(1) {
		counter	 = 0;

		read(connfd,buffer,4096);
		printf("\nClient message:%s",buffer);
		/*
while( (n = read(connfd, buffer, MAXLINE)) >0)
		{

			counter++;
			buffer[n] = 0; //null terminate
			//exception has occured
			if(n<0)
			{
				break;
			}
			if(strstr(buffer, "\r\n") != NULL)
			{
				break;
			}
		}
		if(n<0)
		{
			break;
*/
		//}
		printf("Client: %s",buffer);
		//write out

		printf("\nEnter the message to send\n");
		printf("\nClient: ");

		//write out
		fgets(writebuff,4096,stdin);
		write(connfd,writebuff,4096);
	}
	   Close(connfd);
	   return 0;
}