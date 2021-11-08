#include <iostream>
#include <cstring>
#include <transferUtiltiy.hpp>

#include "transferDataServer.hpp"
#include <network.hpp>
#include <header.hpp>

#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_SERV "8400"

const char *host = NULL;
const char *serv = NULL;

int main(int argc, char **argv) {
	network::NETWORK_INIT netInitializer;
	printf("Server run...\n");
	
	transfer::readCommandLineArg(argc, argv, DEFAULT_HOST, DEFAULT_SERV);
	
	network::socket_t ListenSocket = network::tcpListen(host, serv, AF_UNSPEC);
	do {
		std::cout << "\n\nWait for new connection ... \n";
		try {
			transfer::TransferDataServer t(accept(ListenSocket, NULL, NULL));
			t.run();
		} catch (std::exception &exc) {
			std::cout << "Exception is throw!\n" << exc.what();
		}
	} while(1);
	
	// std::cout << "Press enter for exit server...";
	// std::cin.get();
	return 0;
}
