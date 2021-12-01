
//#ifdef _WIN32
#include <iostream>
#include <winsock2.h>
#include <string>
#include <stdlib.h>

#pragma comment (lib,"ws2_32.lib")
#pragma warning(disable: 4996)

void hello_logo();
void sendMessage(SOCKET Connection);
void sendMessage(SOCKET Connection, std::string message);
void command(SOCKET Connection, std::string cmmd);
void info();
std::string readMessage(SOCKET);



int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	hello_logo();

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	int msgSize = 0;
	char cmd[256];
	if (newConnection == 0) {
				std::cout << "Error Connected!\n";
	}
	else {
		std::cout << "Connected!\n";
		info();
		while (true)
		{
			std::cin.getline(cmd, sizeof cmd);
			//std::cout << cmd << std::endl;
			
			std::string tempp = std::string(cmd);

			if (tempp == "sort by name" or tempp == "sort by type" or tempp == "sort by date") {
				sendMessage(newConnection, cmd);
				std::cout << readMessage(newConnection);
				
			}
			else if (tempp == "Exit" or tempp == "exit") {
				std::cout << "Exit!\n";
				std::cout << "Goodbye\n";
				sendMessage(newConnection, cmd);
				break;
			}
			else {
				std::cout << "Error input! (O_O)\n" << std::endl;
				continue;
			}
		}

	}

	system("pause");
	return 0;
}

void sendMessage(SOCKET Connection)
{
	std::string msg1;
	std::getline(std::cin, msg1);
	int msgSize = msg1.size();
	send(Connection, (char*)&msgSize, sizeof(int), NULL);
	send(Connection, msg1.c_str(), msgSize, NULL);
}

void sendMessage(SOCKET Connection, std::string message)
{
	//send(Connection, (char*)&message, sizeof(message), NULL);
	int msgSize = message.size();
	send(Connection, (char*)&msgSize, sizeof(int), NULL);
	send(Connection, message.c_str(), msgSize, NULL);
}

std::string readMessage(SOCKET Connection)
{
	std::string question;
	int msgSize = 0;
	recv(Connection, (char*)&msgSize, sizeof(int), NULL);

	char* msg = new char[msgSize + 1];
	msg[msgSize] = '\0';
	recv(Connection, msg, msgSize, NULL);
	
	std::string temp = msg;
	delete[] msg;
	return temp;
}

void info() {
	std::cout << "--- --- --- ---" << std::endl;
	std::cout << "command list:" << std::endl;
	std::cout << "sort by name - For sorting folders and files by name (also in subfolders)." << std::endl;
	std::cout << "sort by type - For sorting folders and files by name (also in subfolders)." << std::endl;
	std::cout << "sort by date - This command is not available (under development). (0_0)" << std::endl;
	std::cout << "Exit - To Finish working." << std::endl;
	std::cout << "--- --- --- ---" << std::endl;
}
void command(SOCKET Connection, std::string cmmd){
	std::cout << cmmd << std::endl;
	if (cmmd == "help") {
		std::cout << "--- --- --- ---" << std::endl;
		std::cout << "command list:" << std::endl;
		std::cout << "sort by name - " << std::endl;
		std::cout << "sort by type - " << std::endl;
		std::cout << "sort by date - " << std::endl;

		std::cout << "help - " << std::endl;
		std::cout << "Exit - " << std::endl;
		std::cout << "--- --- --- ---" << std::endl;
	} else if (cmmd == "sort by name") {
		sendMessage(Connection, cmmd);
	} else if (cmmd == "sort by type") {
		sendMessage(Connection, cmmd);
	} else if (cmmd == "sort by date") {
		sendMessage(Connection, cmmd);
	} else {
		std::cout << "Error input! (O_O)" << std::endl;
	}

}
void hello_logo() {
	//system("CLS");
	std::cout << R"(
	____ _    ____ ___  ____ _    _    ____ ____ _ ____    ___ ____ ____ _  _     ___
	| __ |    |  | |__] |__| |    |    |  | | __ | |        |  |__| [__  |_/       |
	|__] |___ |__| |__] |  | |___ |___ |__| |__] | |___     |  |  | ___] | \_     _|_
                                                                             
	)" << '\n';
	std::cout << "----------------------------------\n";
	
}
