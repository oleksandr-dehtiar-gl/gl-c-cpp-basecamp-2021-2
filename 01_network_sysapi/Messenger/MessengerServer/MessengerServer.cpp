#include <iostream>
#include "MessengerNetworking/tcp_server.h"

int main()
{
	tcpServer *server = new tcpServer();
	server->run();
	return 0;
}
