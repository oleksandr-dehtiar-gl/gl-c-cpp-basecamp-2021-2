#ifdef _WIN32
#include <iostream>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma comment (lib,"ws2_32.lib")
#pragma warning(disable: 4996);

#else
#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

using namespace std;

#ifdef _WIN32
std::string rMessage(SOCKET);
void sMessage(SOCKET Connection);
void sMessage(SOCKET Connection, std::string message);

#else 
std::string rMessage(int);
void sMessage(int Connection);
void sMessage(int Connection, std::string message);
#endif
int main(int argc, char *argv[])
{
    #ifdef _WIN32
    WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	int sizeaddr = sizeof(addr);
	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeaddr);

	if (newConnection == 0)
	{
		std::cout << "Error #2\n";
	}

    #else
    int client, newConnection;
    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client<0)
    {
        cout<<"Server error: establishing socket error.";
        exit(0);
    }

    cout<<"Socket for server was successfully created\n";

    server_address.sin_port = htons(1601);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    //int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address));
    int ret = bind(client, (struct sockaddr*)&server_address, sizeof(server_address));
    if(ret < 0)
    {
        cout<<"Error! Binding connection. Socket has already been estabilishing\n";
        return -1;
    }

    socklen_t size = sizeof(server_address);

    cout<<"Listening clients...\n";
    listen(client,1);

    newConnection = accept(client, (struct sockaddr*) &server_address, &size);
    if(newConnection< 0)
    {
        cout<<"Error! Can't accepting client\n";
    }
    #endif
	else
	{
		std::cout << "Client Connected!\n";
		int msgSize = 0;
		while (1)
		{
			sMessage(newConnection);
			std::cout << rMessage(newConnection) << std::endl;
			std::string running = "Running";
			while (rMessage(newConnection) == running)
			{
				std::cout << rMessage(newConnection) << std::endl;
			}
			std::cout << rMessage(newConnection) << std::endl;
		}

        cout<<"Goodbye\n";
        exit(1);
    }
    return 0;
}

#ifdef _WIN32
void sMessage(SOCKET Connection)
{
	std::string msg1;
	std::getline(std::cin, msg1);
	int msgSize = msg1.size();
	send(Connection, (char*)&msgSize, sizeof(int), NULL);
	send(Connection, msg1.c_str(), msgSize, NULL);
}

void sMessage(SOCKET Connection, std::string message)
{
	int msgSize = message.size();
	send(Connection, (char*)&msgSize, sizeof(int), NULL);
	send(Connection, message.c_str(), msgSize, NULL);
}

std::string rMessage(SOCKET Connection)
{
	std::string question;
	int msgSize = 0;
	recv(Connection, (char*)&msgSize, sizeof(int), NULL);

	char* msg = new char[msgSize + 1];
	msg[msgSize] = '\0';
	recv(Connection, msg, msgSize, NULL);
	//std::cout << msg << std::endl;
	std::string temp = msg;
	delete[] msg;
	return temp;
}

#else
void sMessage(int Connection)
{
	std::string msg1;
	std::getline(std::cin, msg1);
	int msgSize = msg1.size();
	send(Connection, (char*)&msgSize, sizeof(int), 0);
	send(Connection, msg1.c_str(), msgSize, 0);
}

void sMessage(int Connection, std::string message)
{
	int msgSize = message.size();
	send(Connection, (char*)&msgSize, sizeof(int), 0);
	send(Connection, message.c_str(), msgSize, 0);
}

std::string rMessage(int Connection)
{
	std::string question;
	int msgSize = 0;
	recv(Connection, (char*)&msgSize, sizeof(int), 0);

	char* msg = new char[msgSize + 1];
	msg[msgSize] = '\0';
	recv(Connection, msg, msgSize, 0);
	std::string temp = msg;
	delete[] msg;
	return temp;
}

#endif