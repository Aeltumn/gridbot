#include "../headers/Logger.h"

//Code Credit to https://jindongpu.wordpress.com/2012/02/06/javac-socket-communication/

void Logger::setup() {
	int sockfd; // socket file descriptor 
	int portno = 4447; // port number
	struct sockaddr_in serv_addr;
	struct hostent *server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // generate file descriptor 
	if (sockfd < 0) return;

	server = gethostbyname("206.189.111.28"); //the ip address (or server name) of the listening server.
	if (server == NULL) return;

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		return;

	char rbuff[256];
	int rbytes;

	info("Started logger system.");
	//rbytes = read(sockfd, rbuff, sizeof(rbuff)); // read from socket and store the msg into buffer
	while (true) {
		//recv should block until something is received
		rbytes = recv(sockfd, rbuff, sizeof(rbuff), 0); // similar to read(), but return -1 if socket closed
		rbuff[rbytes] = '\0'; // set null terminal
		info("Message: %s\n"+rbuff);
	}
}

void Logger::error(const char* str) {
	int wbytes;
	char * wbuff;
	char s[512]; //max length: 512
	strcat(s, "01-01-1970 00:00:00 [ERROR] ");
	strcat(s, str);
	wbytes = write(sockfd, s, strlen(wbuff));
}

void Logger::info(const char* str) {
	int wbytes;
	char * wbuff;
	char s[512]; //max length: 512
	strcat(s, "01-01-1970 00:00:00 [ERROR] ");
	strcat(s, str);
	wbytes = write(sockfd, s, strlen(wbuff));
}