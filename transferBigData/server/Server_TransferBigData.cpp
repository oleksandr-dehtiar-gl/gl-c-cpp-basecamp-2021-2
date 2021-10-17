#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

#include <netApi.hpp>

char bufMSS[MSS_DEFAULT_SIZE];

#define BUF_SIZE 100
char buf[BUF_SIZE];

int main(int argc, char **argv) {
	std::cout << "Hello Server_TransferBigData!\n";

	INIT();
	
	network::socket_t sockListen = network::tcpListen("192.168.0.102", "8400");
	network::socket_t sockConnection = network::Accept(sockListen);
	
	
	// TEST SOMTHING
	/*unsigned int count = BUF_SIZE;
	
	network::Readn(sockConnection, buf, &count);
	
	std::cout << "recive count data: " << count << std::endl;
	fwrite(buf, sizeof(char), count, stdout);
	network::Shutdown(sockConnection, network::SHDWN::RECEIVE);
	
	network::Writen(sockConnection, buf, &count);
	
	network::Shutdown(sockConnection, network::SHDWN::SEND);
	
	std::cout << "\nsend data count: " << count << std::endl;
	*/
	std::ofstream out("copy.mp4", std::ios_base::out | std::ios_base::binary);
	std::filebuf* fbuf = out.rdbuf();
	unsigned int read = MSS_DEFAULT_SIZE;
	network::error_t err = 0;
	auto beginTime = std::clock();
	do {
		err = network::Readn(sockConnection, bufMSS, &read);
		fbuf->sputn(bufMSS, read);
	} while (!((err == 0) && (read != MSS_DEFAULT_SIZE)));
	
	std::cout << "time for send data: " << (std::clock() - beginTime) / CLOCKS_PER_SEC << std::endl;
	
	network::Shutdown(sockConnection, network::SHDWN::RECEIVE);
	
	std::cout << "\nserver close" << std::endl;
	// std::cin.get();
	return 0;
}
