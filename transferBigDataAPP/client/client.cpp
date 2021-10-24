#include <iostream>
#include <fstream>

#include <netApi.hpp>
#include <appExecutionTimer.hpp>
#include <transferUtility.hpp>
#include <packet.hpp>

#include "transferDataClient.hpp"

#define LOCAL_HOST "127.0.0.1"
#define DEFAULT_PORT "8400"

const char *host = NULL;
const char *serv = NULL;

int main(int argc, char **argv) {
	transferApp::AppExecutionTimer applicationRunTime;
	std::cout << "Strat Client_TransferBigData!\n";
	network::INITNETWORK initialize;
	
	transferApp::readCommandLineArg(argc, argv, LOCAL_HOST, DEFAULT_PORT);

	try {
		transferApp::TtransferDataClient clientApp(host, serv);
		clientApp.run();
	} catch (std::exception &exc) {
		std::cerr << exc.what() << std::endl;
	}

	std::cout << "Client close!\n" << std::endl;
	return 0;
}
