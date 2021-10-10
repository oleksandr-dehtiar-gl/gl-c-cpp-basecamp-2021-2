#ifdef _WIN32
#include <iostream>
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <fstream>
#pragma comment (lib,"ws2_32.lib")
#pragma warning(disable: 4996)

#else
#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#endif

using namespace std; 

#ifdef _WIN32
std::string rMessage(SOCKET);
void sMessage(SOCKET Connection, std::string message);
void sMessage(SOCKET Connection);

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

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error failed connect to server\n";
		return 1;
	}

	std::cout << "Connected!\n";

	#else
    int Connection;
    struct sockaddr_in server_address;

    Connection = socket(AF_INET, SOCK_STREAM, 0);
    
    if(Connection<0)
    {
        cout<<"Server error: establishing socket error.";
        exit(0);
    }

    server_address.sin_port = htons(1601);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    cout<<"Client socket created.\n";

    int ret = connect(Connection, (struct sockaddr*)& server_address, sizeof(server_address));
    if(ret == 0)
    {
        cout<<"Connection to server " << inet_ntoa(server_address.sin_addr)<<" with port number " <<1601<<endl;
    }

    cout<<"Waiting for server confirmation.\n";
	#endif

	//notepad change
while (1)
	{
		std::string question = rMessage(Connection);
		std::cout << "Do you want to lounch ";
		std::cout << question << "\nEnter 'Y' to lounch or 'n': ";
		char answer = 'n';
		std::cin >> answer;
		if (answer == 'Y')
		{
			#ifdef _WIN32
			std::string app = "start " + question;
			try { system(app.c_str()); }
			catch (const std::system_error & e) {
				std::cout << "Caught system_error with code " << e.code()
					<< " meaning " << e.what() << '\n';
			}

			#else
			try { system(question.c_str()); }
			catch (const std::system_error & e) {
				std::cout << "Caught system_error with code " << e.code()
					<< " meaning " << e.what() << '\n';
			}
			#endif
			bool successful = 0;
			std::string findApp = "tasklist | findstr \"" +question+"\" > process.txt";
			//system("tasklist | findstr \"notepad.exe\" > process.txt");
			system(findApp.c_str());
			std::ifstream o("process.txt");
			std::string isRun;
			o >> isRun;
			o.close();
			if (isRun.empty() && successful == 0)
			{
				sMessage(Connection, "Failure\n");
				break;
			}
			else
			{
				sMessage(Connection, "Success");
			}
			successful = 1;
			sMessage(Connection, "Running");

			if (successful)
			{
				while (1)
				{
					system(findApp.c_str());
					std::ifstream o("process.txt");
					std::string isRun;
					o >> isRun;
					o.close();
					if (isRun.empty())
					{
						break;
					}

					sMessage(Connection, "Running");
				}
				sMessage(Connection, "Application closed");
			}	
		}
		else
		{
			sMessage(Connection, "The client refused to open the application!");
		}
    }
	#ifdef _WIN32

	#else
    close(Connection);
	#endif
    cout<<"Goodbye!\n";

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