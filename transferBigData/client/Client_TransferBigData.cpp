#include <iostream>
#include <fstream>

#include <netApi.hpp>

#define BUF_SIZE 100
char buf[BUF_SIZE];

char bufMSS[MSS_DEFAULT_SIZE];

int main(int argc, char **argv) {
	std::cout << "Hello Client_TransferBigData!\n";

	INIT();
	
	network::socket_t connectSock = network::tcpConnect("192.168.0.102", "8400");
	
	// TEST SOMTHING
	/*const char *message = "HELLO FUCKING SERVER! SEND ME THIS MESSAGE BACK.";
	unsigned int count = unsigned(strlen(message));

	network::Writen(connectSock, message, &count);
	network::Shutdown(connectSock, network::SHDWN::SEND);
	std::cout << "send data: " << count << std::endl;
	
	network::Readn(connectSock, buf, &count);
	
	std::cout << "recive count data: " << count << std::endl;
	fwrite(buf, sizeof(char), count, stdout);
	
	network::Shutdown(connectSock, network::SHDWN::RECEIVE);
	*/
	
	// =====================
	std::ifstream in("Game.of.Thrones.[S01E01].[tahiy].avi", std::ios_base::in | std::ios_base::binary);
	std::streambuf *fbuf = in.rdbuf();
	unsigned int read = MSS_DEFAULT_SIZE;
	while(read = fbuf->sgetn(bufMSS, MSS_DEFAULT_SIZE)) {
		network::Writen(connectSock, bufMSS, &read);
	}
	network::Shutdown(connectSock, network::SHDWN::SEND);
	// =====================
	
	std::cout << "\nclient close" << std::endl;
	// std::cin.get();
	return 0;
}
