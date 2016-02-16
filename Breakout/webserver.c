#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void myerror() {
    perror("server");
    exit(1);
}

int main() 
{    
    // socket

    int yes = 1;
    int sockfd;

    if (sockfd = socket(PF_INET, SOCK_STREAM, 0), sockfd < 0)
        myerror();
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    // bind

    struct sockaddr_in addr;

    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = PF_INET;
	// Bind to local IP address (convert to Network Byte Order)
    addr.sin_addr.s_addr = htonl(INADDR_ANY);	
	// Convert to Network Byte Order
    addr.sin_port = htons(8080);
    
    if (bind(sockfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) < 0)
        myerror();
    
    // listen

    if (listen(sockfd, 5) < 0)
        myerror();
    
    // accept

    while (1) {
        int clientfd;

        if (clientfd = accept(sockfd, 0, 0), clientfd < 0)
            myerror();
        
        // NOTE 
		// the following part is a quick and dirty illustration of 
		// the concept not complete, and not good programming practice
        
        // read the request
        char buffer[1000];
		char str1[256], str2[256];

        int bytesread = read(clientfd, buffer, sizeof(buffer)-1);
        buffer[bytesread] = 0;

        printf("%s", buffer);
 
		// check if it is a GET message
        if (strncmp(buffer, "GET", 3) == 0) {
			sscanf(buffer, "%s %s", str1, str2);
		}
		else {
			close(clientfd);
			continue;
		}

        // not implemented, just hardcoded filename
        char filename[500] = "test.html";
        
        // open and read file
        char filebuffer[10000];
        
        FILE *fp = fopen(filename, "r");
        int filelen = fread(filebuffer, 1, sizeof(filebuffer), fp);
        
        // write response
        char msg[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        char htmlresponse[1000000];

        strcpy(htmlresponse, msg);
        strcat(htmlresponse, filebuffer);
        write(clientfd, htmlresponse, strlen(htmlresponse));
        
        // close

        close(clientfd);
    }

    return 0;
}
