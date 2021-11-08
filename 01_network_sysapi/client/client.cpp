#include <iostream>

#include "transferDataClient.hpp"
#include <network.hpp>
#include <transferUtiltiy.hpp>
#include <appExecutionTimer.hpp>

#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_SERV "8400"

const char *host = NULL;
const char *serv = NULL;

int main(int argc, char **argv) {
	network::NETWORK_INIT netInitializer;
	printf("Client run...\n");
	transfer::AppExecutionTimer timer;
	
	transfer::readCommandLineArg(argc, argv, DEFAULT_HOST, DEFAULT_SERV);
	
	transfer::TransferDataClient t(network::tcpConnect(host, serv, AF_UNSPEC));
	t.run();
	
	// std::cout << "Press enter for exit client...";
	// std::cin.get();
	return 0;
}
