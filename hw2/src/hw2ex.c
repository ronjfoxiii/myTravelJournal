#include <stdio.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include "hw2.h"

int sockfd; // The socket pointer you'll use
void cleanExit() {
	// close sockfd
	close(sockfd);
	exit(0);
}

#define BUFFSIZE 2048

int main(int argc, char *argv[]) {
	signal(SIGTERM, cleanExit);
	signal(SIGINT, cleanExit);
	int newsockfd; // The socket you get with a connection
	int port; // The port you listen on
	int clilen; // The length of the client's address
	char* res; // stores the result
	int yes = 1;

	struct sockaddr_in serv_addr; // The server's address
	struct sockaddr_in cli_addr; // The client's address

	char buffer[BUFFSIZE]; // a buffer to read results to.
	int n; // number of bytes read

	// set clilent to size of client address struct
	clilen = sizeof(cli_addr);

	// allocate sockfd by calling 'socket'
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Could not open socket");
		return EXIT_FAILURE;
	}

	// You should look up what this does if you don't know.
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&yes, sizeof(int) );

	// Set the port number based on the first command line argument
	port = (argc > 1) ? atoi(argv[1]) : 8000;

	// Zero-out the server address
	bzero((void*) &serv_addr, sizeof(serv_addr));

	// initialize the socket structure (i.e., set the values of serv_addr)
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	// bind the host address
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		return EXIT_FAILURE;
	}

	// Listen for a client.
	listen(sockfd, 1);

	while (1) { // go forever!
		// Accept actual connection from the client
		if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
			perror("ERROR on accept");
			return EXIT_FAILURE;
		}

		// read from the socket
		if ((n = read(newsockfd, buffer, BUFFSIZE, 0)) > 0) {
			printf("%s", buffer);
			res = handle_request(buffer);
			write(newsockfd, res, strlen(res),0);
			bzero(buffer, BUFFSIZE);
			free(res);
		}

		// close newsockfd
		close(newsockfd);
	}
	// close sockfd
	close(sockfd);

	exit(0);
}
