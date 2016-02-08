#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>
#define SA      struct sockaddr 
int main(int argc, char ** argv)
{
	time_t ticks;
	struct sockaddr_in servaddr, cliaddr;
	char buff[1024];
	int len, connfd;
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family 	 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port 	 = htons(13057);

	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	
	for(;;)
	{
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *) &cliaddr, &len);
		printf("Connection from %s, port %d\n",
			inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
			ntohs(cliaddr.sin_port));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));

		close(connfd);
	}
	return 0;
}
