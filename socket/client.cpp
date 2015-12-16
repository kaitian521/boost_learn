#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(0);
}

const int nn = 1000000;
char buffer[nn];
int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	int a = 2;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &a, sizeof(int)) == -1) {
		    fprintf(stderr, "Error setting socket opts: %s\n", strerror(errno));
	}

    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    while(fgets(buffer,255,stdin)) {
		cout << "begin to write..." << endl;
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			 error("ERROR writing to socket");
		else {
			cout << "write success..." << endl;
		}
		bzero(buffer,256);
		while((n = read(sockfd,buffer,nn)) > 0) {
			if (n < 0) 
				 error("ERROR reading from socket");
			//printf("%s\n",buffer);
			//usleep(1*1000);
		}
		printf("begin to read fron stdin... \n");
	}
    return 0;
}
