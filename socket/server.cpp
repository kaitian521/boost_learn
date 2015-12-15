/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cmath>
#include <stdio.h>
#include <algorithm>    // std::max

using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 int yes = 1;
	 int op ;
	 if ( (op = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ) < 0) {
		 printf("SO_REUSEADDR error\n");
	 }
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

	 /*for (int i = 0;;i++) {
		 newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
		 if (newsockfd < 0) 
			  error("ERROR on accept");
		 int pid;
		 if ((pid = fork()) == 0) {
			 //close (sockfd);
			 char buff[1000];
			 printf("connction from %s, port %d\n", inet_ntop(AF_INET, &cli_addr.sin_addr, buff, sizeof(buff)), ntohs(cli_addr.sin_port));
			 bzero(buffer,256);
			 n = read(newsockfd,buffer,255);
			 if (n < 0) error("ERROR reading from socket");
			 printf("Here is the message: %s\n",buffer);
			 n = write(newsockfd,"I got your message",18);
			 if (n < 0) error("ERROR writing to socket");
			 close (newsockfd);
		 }
		 else {
			close (newsockfd);
		 }
	 }*/


     //set of socket descriptors
	 fd_set readfds;

	 int clients[1024];
	 int maxFd = -1;
	 memset(clients, 0, sizeof(clients));

	 while (true) {
		 FD_ZERO(&readfds);
		 FD_SET(sockfd, &readfds);
		 maxFd = sockfd;
		 for (int i = 0; i < 1024; i++) {
			 if (clients[i]) {
				 maxFd = std::max(maxFd, clients[i]);
				 FD_SET(clients[i], &readfds);
				 printf("client %d is active", clients[i]);
			 }
		 }

		 int ret = select(maxFd + 1, &readfds, NULL, NULL, NULL);

		 if (ret < 0 && errno != EINTR) {
			 printf("select error");
			 continue;
		 }

		 if (FD_ISSET(sockfd, &readfds)) {
			 printf("begin to accept socket %d...", sockfd);
			 int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
			 for (int j = 0; j < 1024; j++) {
				 if (clients[j] == 0) {
					 clients[j] = newsockfd;
					 break;
				 }
			 }
			 char buff[1000];
			 printf("connction from %s, port %d\n", inet_ntop(AF_INET, &cli_addr.sin_addr, buff, sizeof(buff)), ntohs(cli_addr.sin_port));
		 }

		 for (int i = 0; i < 1024; i++) {
			 if (clients[i]) {
				 if (FD_ISSET(clients[i], &readfds)) {
					 int len;
					 memset(buffer, 0, sizeof(buffer));
					 if ( (len = read(clients[i],buffer,255)) == 0) {
						 printf("client close connection...");
						 close(clients[i]);
						 clients[i] = 0;
					 }
					 else {
						  printf("Here is the message: %s\n",buffer);
						  n = write(clients[i],"I got your message",18);
					 }
				 }
			 }
		 }

	 }


     return 0; 
}
