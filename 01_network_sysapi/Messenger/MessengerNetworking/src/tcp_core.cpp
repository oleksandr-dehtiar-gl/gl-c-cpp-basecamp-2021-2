#include "MessengerNetworking/tcp_core.h"
int TCPCORE::tcpCore::initializeWinsock(){
	ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsOk << std::endl;
		return wsOk;
	}
}
decltype(INVALID_SOCKET) TCPCORE::tcpCore::createSocket(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET)
        {
            auto error = WSAGetLastError();
            std::cerr << "Can't create socket, Err #" << error << std::endl;
            WSACleanup();
            return error;
        }
}