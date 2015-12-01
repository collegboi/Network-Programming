#include "unp.h" 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#define HOME_PAGE "<html>PageFound</html>"
#define ERROR_PAGE "<html>Error 404</html>"

int main(int argc, char **argv)
{
	int	listenfd,connfd; //socket IDs; one for the listening socket and one for the connected socket 
	struct 	sockaddr_in servaddr; //address structure to hold this server's address
	char 	readbuff[MAXLINE];
	char 	writebuff[MAXLINE];
	char	cmd[16];
	char	path[64];
	char	path1[65];
	char	vers[16];
	int n =0;

	if(argc != 2) //verifies number of command-line args; two in this instance
		err_quit("usage: <Program Name> <Port No.>");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0); //create socket

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family 	=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port	=htons(atoi(argv[1]));

	Bind(listenfd, (SA *) &servaddr,sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for( ; ; )
	{
		connfd = Accept(listenfd, (SA *) NULL, NULL);

		while( (n = read(connfd, readbuff, MAXLINE)) >0)
		{
			//exception has occured
			if(n<0)
			{
				break;
			}
			// read into the write buff, method, resource, version
			sscanf(readbuff, "%s %s %s",cmd, path, vers);
			//until the END of the header
			if(strstr(readbuff, "\r\n\r\n") != NULL)
			{
				break;
			}
		}
		if(n<0)
		{
			break;
		}

		int ch;
		FILE *fp;
		int count = 0;

		snprintf(path1, sizeof(path1), ".%s", path);

		//printf("Test %s", path1);

		fp = fopen(path1,"r"); // read mode
		//no files
		if( fp == NULL )
		{
			fp = fopen("./error.html","r");

			while( ( ch = fgetc(fp) ) != EOF ) {

				//strcpy(writebuff, ch);
				writebuff[count] = ch;
				count++;
			}

			/* snprintf(writebuff, sizeof(writebuff), "%s", writebuff); */
			Write(connfd, writebuff, strlen(writebuff));

			fclose(fp);
			//ERROR PAGE
			//write back to the client that no index.html was found
			/*
snprintf(writebuff, sizeof(writebuff), "%s", ERROR_PAGE);
			Write(connfd, writebuff, strlen(ERROR_PAGE));
*/

		} else {

			while( ( ch = fgetc(fp) ) != EOF ) {

				//strcpy(writebuff, ch);
				writebuff[count] = ch;
				count++;
			}

			/* snprintf(writebuff, sizeof(writebuff), "%s", writebuff); */
			Write(connfd, writebuff, strlen(writebuff));

			fclose(fp);
		}

		Close(connfd);
	}
	return 0;
}