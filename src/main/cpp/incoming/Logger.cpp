#include "../headers/Logger.h"
#include <string.h>
#include <ctime>
#include <iostream>

#if defined(__linux__) || defined(__CYGWIN__)
//Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//Code Credit to https://jindongpu.wordpress.com/2012/02/06/javac-socket-communication/

int sockfd; // socket file descriptor 

void Logger::setup() {
	int portno = 4447; // port number
	struct sockaddr_in serv_addr;
	struct hostent *server;

	info("Starting logger setup...");

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // generate file descriptor 
	if (sockfd < 0) {
		error("Error with setting up socket file descriptor.");
		return;
	}

	server = gethostbyname("206.189.111.28"); //the ip address (or server name) of the listening server.
	if (server == NULL) {
		error("Error with getting hostname for listening server.");
		return;
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	info("Initialised socket connection target and descriptor, attempting to connect...");

	try {
		if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
			error("Error with connecting to socket.");
			return;
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}

	char rbuff[256];
	int rbytes;

	info("Succesfully started and connected logger system.");
	//rbytes = read(sockfd, rbuff, sizeof(rbuff)); // read from socket and store the msg into buffer
	while (true) {
		strcat(rbuff, "Received: ");
		//recv should block until something is received
		rbytes = recv(sockfd, rbuff, sizeof(rbuff), 0); // similar to read(), but return -1 if socket closed
		rbuff[rbytes] = '\0'; // set null terminal
		info(rbuff);
	}
}

void Logger::error(const char* str) {
	int wbytes;
	char s[512]; //max length: 512
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", timeinfo);
	strcat(s, " [ERROR] ");
	strcat(s, str);
	strcat(s, "\n");
	std::cout << s;
	wbytes = send(sockfd, s, (int)strlen(s), 0);
}

void Logger::info(const char* str) {
	int wbytes;
	char s[512]; //max length: 512
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", timeinfo);
	strcat(s, " [INFO] ");
	strcat(s, str);
	strcat(s, "\n");
	std::cout << s;
	wbytes = send(sockfd, s, (int)strlen(s), 0);
}
#else
//Windows
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

SOCKET sock;
SOCKADDR_IN addr;

void Logger::setup() {
	try {
		//Start winsock
		WSADATA wsaData;

		//activate ws2_32.lib
		int res = WSAStartup(MAKEWORD(2, 0), &wsaData);
		if (res != 0) {
			error("Error with WSAStartup");
			return;
		}

		//Create Client Socket
		sock = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP); // generate file descriptor 
		if (sock == INVALID_SOCKET) {
			error("Socket failed to start up!");
			return;
		}

		addr.sin_port = 4447; // port number
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_un_b.s_b1 = 206;
		addr.sin_addr.S_un.S_un_b.s_b2 = 189;
		addr.sin_addr.S_un.S_un_b.s_b3 = 111;
		addr.sin_addr.S_un.S_un_b.s_b4 = 28;

		if (connect(sock, (SOCKADDR*)(&addr), sizeof(addr)) == SOCKET_ERROR) {
			error("Error while trying to establish socket connection.");
			return;
		}

		char rbuff[512];
		int rbytes;

		info("Started logger system.");
		//rbytes = read(sockfd, rbuff, sizeof(rbuff)); // read from socket and store the msg into buffer
		while (true) {
			//recv should block until something is received
			rbytes = recv(sock, rbuff, sizeof(rbuff), 0); // similar to read(), but return -1 if socket closed
			rbuff[rbytes] = '\0'; // set null terminal
			info(rbuff);
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}
}

void Logger::error(const char* str) {
	int wbytes;
	char s[512]; //max length: 512
	struct tm buf;
	time_t t = time(NULL);
	localtime_s(&buf, &t);
	strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", &buf);
	strcat_s(s, " [ERROR] ");
	strcat_s(s, str);
	strcat_s(s, "\n");
	std::cout << s;
	wbytes = send(sock, s, (int)strlen(s), 0);
}

void Logger::info(const char* str) {
	int wbytes;
	char s[512]; //max length: 512
	struct tm buf;
	time_t t = time(NULL);
	localtime_s(&buf, &t);
	strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", &buf);
	strcat_s(s, " [INFO] ");
	strcat_s(s, str);
	strcat_s(s, "\n");
	std::cout << s;
	wbytes = send(sock, s, (int)strlen(s), 0);
}
#endif