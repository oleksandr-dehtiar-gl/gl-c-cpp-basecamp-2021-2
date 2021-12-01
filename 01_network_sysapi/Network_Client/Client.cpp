
#include <iostream>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <string>

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::recursive_directory_iterator;


#pragma comment (lib,"ws2_32.lib")
#pragma warning(disable: 4996)


#include <stdlib.h>
#include <stdio.h>


void sendMessage(SOCKET Connection);
void sendMessage(SOCKET Connection, std::string message);
std::string readMessage(SOCKET);

std::string demo_status(const fs::path& p, fs::file_status s);
string sortByNameOrType(string typeOrName, string basicPath);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	std::string basicPath = "./forSort";
	//WSAStartup
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

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	else {
		std::cout << "Connected!\n";
		
		std::string tempp;
		while (true)
		{
			try {
				tempp = readMessage(Connection);
				std::cout << "the message is received: " << std::endl;
				// ---
				/*std::string path = "./forSort";
				for (const auto& entry : fs::directory_iterator(path))
					std::cout << entry.path() << std::endl;*/

					// ---
				if (tempp == "Exit" or tempp == "exit") {
					std::cout << "Exit!\n";
					std::cout << "Goodbye\n";
					break;
				}
				else if (tempp == "sort by name") {
					cout << sortByNameOrType("name", basicPath) << endl;
					sendMessage(Connection, sortByNameOrType("name", basicPath) + "\n --- done --- \n\n");
				}
				else if (tempp == "sort by type") {
					cout << sortByNameOrType("type", basicPath) << endl;
					sendMessage(Connection, sortByNameOrType("type", basicPath) + "\n --- done --- \n\n");
				}
				else if (tempp == "sort by date") {
					std::cout << "sort by date - This command is not available (under development). (0_0)\n";
					sendMessage(Connection, "sort by date - This command is not available (under development). (0_0)\n");
				}
				else {
					std::cout << "error imput (O_O)\n";
				}
			}
			catch (...) {
				sendMessage(Connection, "(O_o)\n(O_o)\n(O_o)\n Not performed. ");
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

std::string demo_status(const fs::path& p, fs::file_status s)
{
	// vector<string> v = split (str, '+'); ./forSort\\
    /*std::cout << p;*/
	switch (s.type())
	{
	case fs::file_type::none: /*std::cout << "has `not-evaluated-yet` type";*/ return "has `not-evaluated-yet` type"; break;
	case fs::file_type::not_found: /*std::cout << "does not exist";*/ return "does not exist"; break;
	case fs::file_type::regular: /*std::cout << "is a regular file";*/ return "is a regular file"; break;
	case fs::file_type::directory: /*std::cout << "is a directory";*/ return "is a directory"; break;
	case fs::file_type::symlink: /*std::cout << "is a symlink";*/ return "is a symlink"; break;
	case fs::file_type::block: /*std::cout << "is a block device";*/ return "is a block device"; break;
	case fs::file_type::character: /*std::cout << "is a character device";*/ return "is a character device"; break;
	case fs::file_type::fifo: /*std::cout << "is a named IPC pipe";*/ return "is a named IPC pipe"; break;
	case fs::file_type::socket: /*std::cout << "is a named IPC socket";*/ return "is a named IPC socket"; break;
	case fs::file_type::unknown: /*std::cout << "has `unknown` type";*/ return "has `unknown` type"; break;
	default: /*std::cout << "has `implementation-defined` type";*/ return "has `implementation-defined` type"; break;
	}
	std::cout << '\n';
}

string sortByNameOrType(string typeOrName, string basicPath) {
	string strForReturn;
	//std::string path = "./forSort";
	list<string> myFiles;
	for (auto it = fs::directory_iterator(basicPath); it != fs::directory_iterator(); ++it) {
		demo_status(*it, it->symlink_status());

		//cout << it->path().u8string() << endl;

		//cout << "name - " << it->path().u8string().substr(10) << endl;
		//cout << demo_status(*it, it->symlink_status()) << endl;

		//wcout << DisplayPathInfo(it->path()) << endl;

		if (typeOrName == "name") {
			if (demo_status(*it, it->symlink_status()) == "is a directory") {
				myFiles.push_back(it->path().u8string().substr(10) + " - " + demo_status(*it, it->symlink_status())
					+ ": \n" + sortByNameOrType("name", basicPath + "/" + it->path().u8string().substr(10)));
			}
			else {
				myFiles.push_back(it->path().u8string().substr(10));// +" - " + demo_status(*it, it->symlink_status()));
			}


		}
		else if (typeOrName == "type") {

			if (demo_status(*it, it->symlink_status()) == "is a directory") {
				myFiles.push_back(demo_status(*it, it->symlink_status()) + " - " + it->path().u8string().substr(10)
					+ ": \n" + sortByNameOrType("type", basicPath + "/" + it->path().u8string().substr(10)));
			}
			else {
				myFiles.push_back(demo_status(*it, it->symlink_status()) + " - " + it->path().u8string().substr(10));
			}
		}
		else {
			strForReturn = "ERROR! :(";
		}
		//cout << "\n -- -- --" << endl;
	}
	if (strForReturn == "ERROR! :(") {
		return strForReturn;
	}
	else {
		myFiles.sort();
		for (auto it = myFiles.begin(); it != myFiles.end(); ++it) {
			//cout << ' ' << *it << endl;
			strForReturn += *it + "\n";
		}
	}

	return strForReturn;
}
