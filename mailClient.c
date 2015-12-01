#include "unp.h"
#include <errno.h>

int readLine(int sock) {

	printf("\r\n");
	char line[MAXLINE];
	int n = 0;
	int counter = 0;
	while( (n = read(sock, line, MAXLINE)) >0)
	{
		counter++;
		line[n] = 0; //null terminate
		if(fputs(line, stdout) == EOF)
		{ //print data time and data returned from server
			err_sys("fputs error");
		}

		if(strstr(line, "\r\n\r\n") != NULL){
			break;
		}

		break;
	}

	return n;
}

int main(int argc, char **argv)
{
	int sockfd = 0;
	char buff[MAXLINE];
	struct sockaddr_in servaddr;

	if(argc != 3)
		err_quit("usage:a.out <IPaddress>");

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0 )
		err_sys("connect error");


	if(readLine(sockfd) > 0) {
		char newBuff[] =  "HELO 147.252.234.34\r\n";
		Write(sockfd, newBuff, strlen(newBuff));

		if(readLine(sockfd) > 0) {

			char mail[] = "MAIL FROM: <cindy.lou@gmail.com>\r\n";
			Write(sockfd, mail, strlen(mail));

			if(readLine(sockfd) > 0 ) {
				char recep[] = "RCPT TO: <stephenfox995@gmail.com>\r\n";
				Write(sockfd, recep, strlen(recep));

				if(readLine(sockfd) > 0)  {
					char data[] = "DATA\r\n";
					Write(sockfd, data, strlen(data));

					if(readLine(sockfd) > 0) {

						char dataRec1[] = "From: cindy.lou@gmail.com\r\n";
						Write(sockfd, dataRec1, strlen(dataRec1));

						char dataRec2[] = "To: stephenfox995@gmail.com\r\n";
						Write(sockfd, dataRec2, strlen(dataRec2));

						char dataRec3[] = "Subject: Cindy Lou\r\n";
						Write(sockfd, dataRec3, strlen(dataRec3));

						char dataRec4[] = "\r\n";
						Write(sockfd, dataRec4, strlen(dataRec4));

						char dataRec5[] = "I have kinky boots and lookign for some fun\r\n";
						Write(sockfd, dataRec5, strlen(dataRec5));

						char value1[] = "\r\n";
						Write(sockfd, value1, strlen(value1));

						char value2[] = ".\r\n";
						Write(sockfd, value2, strlen(value2));

						readLine(sockfd);

					}
				}
			}
		}
	}



	exit(0);
}

