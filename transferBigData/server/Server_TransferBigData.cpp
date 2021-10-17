#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

#include <netApi.hpp>
#include <transferUtility.hpp>

char bufMSS[MSS_DEFAULT_SIZE];

#define BUF_SIZE 100
char buf[BUF_SIZE];

int main(int argc, char **argv) {
	std::cout << "Hello Server_TransferBigData!\n";

	// TEST SOMTHING
	std::string dirName;
	if (argc == 2)
		dirName = argv[1];
	else 
		dirName = "build";
		
	std::vector<transferUtil::fileNameSize_p> fileList = transferUtil::getFilesFromDir(dirName);
	
	for (auto &a : fileList) {
		std::cout << " -- [" << std::get<1>(a) << "] - " << std::get<0>(a) << std::endl;
	}
	
	//This banch of code receive file to server. Code of client in file client
	/*	INIT();
		network::socket_t sockListen = network::tcpListen(NULL, "8400");
		network::socket_t sockConnection = network::Accept(sockListen);
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
	*/
	
	std::cout << "\nserver close" << std::endl;
	// std::cin.get();
	return 0;
}
