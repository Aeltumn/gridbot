#include "../headers/Logger.h"
#include <string>
#include <ctime>
#include <iostream>

//Code Credit to https://jindongpu.wordpress.com/2012/02/06/javac-socket-communication/

int sockfd; // socket file descriptor 

void Logger::setup() {
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
		info(rbuff);
	}
}

void Logger::error(const char* str) {
	int wbytes;
	char * wbuff;
	char s[512]; //max length: 512
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", timeinfo);
	strcat(s, " [ERROR] ");
	strcat(s, str);
	std::cout << s;
	wbytes = send(sockfd, s, strlen(wbuff), 0);
}

void Logger::info(const char* str) {
	int wbytes;
	char * wbuff;
	char s[512]; //max length: 512
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", timeinfo);
	strcat(s, " [INFO] ");
	strcat(s, str);
	std::cout << s;
	wbytes = send(sockfd, s, strlen(wbuff), 0);
}