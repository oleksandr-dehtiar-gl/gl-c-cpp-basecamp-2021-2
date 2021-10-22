#include <iostream>
#include "MessengerNetworking/tcp_client.h"

int main()
{
	std::cout << "Input ip: ";
	std::string ipAdress;
	getline(std::cin, ipAdress);
	tcpClient * client = new tcpClient(ipAdress);
	client->run();
	delete client;
	return 0;
}
