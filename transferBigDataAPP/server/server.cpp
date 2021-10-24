#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <utility>
#include <list>

#include <netApi.hpp>
#include <transferUtility.hpp>
#include <threadGuard.hpp>

#include "transferDataServer.hpp"

#define MSS_DEFAULT_SIZE 1200
char bufMSS[MSS_DEFAULT_SIZE];

#define BUF_SIZE 100
char buf[BUF_SIZE];

////////////////////////////////////////////
#define LOCAL_HOST "127.0.0.1"
#define DEFAULT_PORT "8400"

const char *host = NULL;
const char *serv = NULL;
////////////////////////////////////////////

int main(int argc, char **argv) {
	std::cout << "Start Server_TransferBigData!\n";
	network::INITNETWORK initialize;
	
	transferApp::readCommandLineArg(argc, argv, LOCAL_HOST, DEFAULT_PORT);
	auto listenSock = network::tcpListen(host, serv);

	do {
		std::cout << "\nWaiting for connection\n";
		try {
			transferApp::TtransferDataServer task(transferApp::SocketConnection(network::Accept(listenSock)));
			transferApp::Threadguard threadTask(std::thread(&transferApp::TtransferDataServer::run, std::ref(task)));
		} catch (std::exception &exc) {
			std::cout << exc.what() << std::endl;
			continue;
		}
	} while(1);

	
	std::cout << "\nServer close" << std::endl;
	std::cin.get();
	return 0;
}
