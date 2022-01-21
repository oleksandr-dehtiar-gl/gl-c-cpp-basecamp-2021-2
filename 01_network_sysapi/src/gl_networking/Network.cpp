#include "Network.h"
#include <iostream>

bool Network::Initialize()
{
	#ifdef _WIN32
	WSADATA wsdata;
	int result = WSAStartup(MAKEWORD(2, 2), &wsdata);
	if (result != 0)
	{
		std::cerr << "Initialization failed" << std::endl;
		return false;
	}
	if (HIBYTE(wsdata.wVersion) != 2 || LOBYTE(wsdata.wVersion) != 2)
	{
		std::cerr << "Invalid WSA version" << std::endl;
		return false;

	}
	#endif
	return true;
	
}

void Network::Shutdown()
{
	#ifdef _WIN32
	WSACleanup();
	#endif
}

