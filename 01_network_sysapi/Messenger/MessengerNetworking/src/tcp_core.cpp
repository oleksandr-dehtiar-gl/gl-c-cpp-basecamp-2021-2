#include "MessengerNetworking/tcp_core.h"
int TCPCORE::tcpCore::initializeWinsock(){
	ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
		throw new std::exception(("Can't start Winsock, Err #" + std::to_string(wsOk)).c_str());
    return wsOk;
}
decltype(INVALID_SOCKET) TCPCORE::tcpCore::createSocket(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
        throw new std::exception(("Can't create socket, Err #" + std::to_string(WSAGetLastError())).c_str());
    return 0;
}
void TCPCORE::tcpCore::disconnect(){
    	closesocket(sock);
		WSACleanup();
}
void TCPCORE::tcpCore::run(){
    	try{
            connect();
        }
        catch(std::exception* ex){
            std::cerr << ex->what() << std::endl;
            disconnect();
        }
}