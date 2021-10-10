#include <iostream>

#include <netApi.hpp>

#include <cassert>


int main(int argc, char **argv) {
	std::cout << "Hello Server_TransferBigData!\n";

	INIT();
	
	assert (8400 == network::tcp_server("127.0.0.1", "8400"));
	
	std::cin.get();
	return 0;
}