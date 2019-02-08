#include "pch.h"
#define PORT 447

bool connected = false;
bool Logger::isConnected() { return connected; }

//Code Credit to https://jindongpu.wordpress.com/2012/02/06/javac-socket-communication/
int sockfd; // socket file descriptor 

void Logger::setup() {
	try {
		int portno = PORT; // port number
		struct sockaddr_in serv_addr;
		struct hostent *server;

		info("[LOGGER] Starting logger setup...");

		sockfd = socket(AF_INET, SOCK_STREAM, 0); // generate file descriptor 
		if (sockfd < 0) {
			error("[LOGGER] Error with setting up socket file descriptor.");
			return;
		}

		server = gethostbyname("206.189.111.28"); //the ip address (or server name) of the listening server.
		if (server == NULL) {
			error("[LOGGER] Error with getting hostname for listening server.");
			return;
		}

		bzero((char *)&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
		serv_addr.sin_port = htons(portno);
		info("[LOGGER] Initialised socket connection target and descriptor, attempting to connect...");
		char buf[256];
		buf[0] = 0;
		strcat(buf, "[LOGGER] Using port: ");
		strcat(buf, std::to_string(PORT).c_str());
		strcat(buf, ".");
		info(buf);

		if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
			error("[LOGGER] Error with connecting to socket.");
			return;
		}

		char rbuff[512];
		rbuff[0] = 0;
		int rbytes;

		info("[LOGGER] Succesfully started and connected logger system.");
		connected = true;
		//rbytes = read(sockfd, rbuff, sizeof(rbuff)); // read from socket and store the msg into buffer
		while (true) {
			//recv should block until something is received
			rbytes = recv(sockfd, rbuff, sizeof(rbuff), 0); // similar to read(), but return -1 if socket closed
			rbuff[rbytes] = 0;
			info(rbuff);
			if (handleCommand(rbuff)) abort();
	} catch (const std::exception& e) {
		info(e.what());
		return;
	}
}

// The various types of logs
void Logger::info(const char* txt) { log(true, " [INFO] ", txt); }
void Logger::error(const char* txt) { log(true, " [ERROR] ", txt); }
void Logger::warning(const char* txt) { log(true, " [WARNING] ", txt); }
void Logger::amend(const char* txt) { log(false, "", txt); }
void Logger::newline() { log(false, "", ""); }
 
// The function where we log, some types have a timestamp, some have a prefix.
void Logger::log(bool time_, const char* prefix, const char* str) {
	char s[512]; //max length: 512
	s[0] = 0;
	if (time_) {
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(s, sizeof(s), "%d-%m-%Y %H:%M:%S", timeinfo);
	}
	strcat(s, prefix);
	strcat(s, str);
	strcat(s, "\n");
	strcat(s, "\0");
	std::cout << s;
	if(connected) send(sockfd, s, (int)strlen(s), 0);
}

// We handle comamnds incoming from grinterface.dgoossens.nl here.
bool Logger::handleCommand(const char* txt) {
	std::vector<std::string> args;
	std::stringstream stream;
	int i = 0;
	char in;
	while ((in = *(txt + i)) != 0) {
		//Keep reading until we find a null terminator
		if (in == ' ') {
			std::string str = stream.str();
			stream.str(std::string());
			args.push_back(str);
		} else {
			stream << in;
		}
		i++;
		if (i >= 512) break; // txt can't be larger than 512
	}
	args.push_back(stream.str());

	if (args.size() == 0) return;
	std::string command = args.at(0);
	if (command.compare("execute") == 0 || command.compare("e") == 0) { // Executes the next move.
		Beta::execute();
	} else if (command.compare("magnet") == 0) {
		if (args.size() >= 2) {
			if (args.at(1).compare("on") == 0) {
				GPIO::set(10, true);
				Logger::info("[LOGGER] Turned on magnet.");
			} else {
				GPIO::set(10, false);
				Logger::info("[LOGGER] Turned off magnet.");
			}
		} else {
			Logger::error("[LOGGER] Invalid syntax! Use: magnet on|off");
		}
	} else if (command.compare("handlemove") == 0 || command.compare("hm") == 0) {
		if (args.size() >= 1) {
			int i = std::stoi(args.at(1), nullptr, 10);
			char buf[256];
			buf[0] = 0;
			strcat(buf, "[LOGGER] Registered opponent move of ");
			strcat(buf, std::to_string(i).c_str());
			strcat(buf, ".");
			Logger::info(buf);
			Beta::handleMove(i);
		} else {
			Logger::error("[LOGGER] Invalid syntax! Use: tictactoe int");
		}
	} else if (command.compare("tictactoe") == 0 || command.compare("ttt") == 0) {
		if (args.size() >= 1) {
			int i = std::stoi(args.at(1), nullptr, 10);
			TicTacToe *t = new TicTacToe(i == 1 ? true : false);
			if(i == 1) Logger::info("[LOGGER] Starting game of tic tac toe whilst starting.");
			else Logger::info("[LOGGER] Starting game of tic tac toe.");
			Beta::runGame(t);
		} else {
			Logger::error("[LOGGER] Invalid syntax! Use: tictactoe int");
		}
	} else if (command.compare("testmotors") == 0 || command.compare("m") == 0) {
		if (args.size() >= 3) {
			std::string axis = args.at(1);
			int i = std::stoi(args.at(2), nullptr, 10);
			char buf[256];
			buf[0] = 0;
			strcat(buf, "[LOGGER] Moving ");
			strcat(buf, std::to_string(i).c_str());
			strcat(buf, " centimetres.");
			Logger::info(buf);
			Beta::getmotor(axis.compare("x") == 0 ? 0 : axis.compare("y") == 0 ? 1 : 2)->queue(i);
			Logger::info("[LOGGER] Moved target axis target distance.");
		} else {
			Logger::error("[LOGGER] Invalid syntax! Use: testmotors x|y|z int");
		}
	} else if (command.compare("help") == 0) {
		Logger::info("[LOGGER] De volgende commands bestaan:");
		Logger::amend("execute - Speelt de volgende beurt van het huidige spel.");
		Logger::amend("testmotors x|y|z int - Beweeg de x, y of z as met int centimeter.");
		Logger::amend("magnet on|off - Zet de magneet aan of uit.");
		Logger::amend("handlemove int - Registreer de zet van de tegenstander naar index int.");
		Logger::amend("tictactoe int - Start boter kaas en eieren, int is 1 voor first, anders 0.");
		Logger::amend("restart - Herstart gridbot.");
		Logger::newline();
		Logger::info("[LOGGER] De volgende aliases bestaan:");
		Logger::amend("m - testmotors");
		Logger::amend("hm - handlemove");
		Logger::amend("e - execute");
		Logger::amend("ttt - tictactoe");
	} else if (command.compare("restart") == 0) {
		return true;
	}
	return false;
}