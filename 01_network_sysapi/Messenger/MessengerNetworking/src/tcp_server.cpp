#include "MessengerNetworking/tcp_server.h"
void tcpServer::bind(){
    hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(conPort);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	
	::bind(sock, (sockaddr*)&hint, sizeof(hint));
}
void tcpServer::run(){
    connect();
}
void tcpServer::connect(){
    initializeWinsock();
    createSocket();
    bind();
    listen(sock, SOMAXCONN);
    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(sock, (sockaddr*)&client, &clientSize);
    char host[NI_MAXHOST]; //client's name
    char service[NI_MAXSERV]; //client's connection port
    ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		std::cout << host << " connected on port " << service << std::endl;
	else
	{
		strcpy(host, inet_ntoa(client.sin_addr));
		std::cout << host << " connected on port " <<
			ntohs(client.sin_port) << std::endl;
	}
    closesocket(sock);
    char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			std::cerr << "Error in recv(). Quitting" << std::endl;
			break;
		}

		if (bytesReceived == 0)
		{
			std::cout << "Client disconnected " << std::endl;
			break;
		}

		std::cout << std::string(buf, 0, bytesReceived) << std::endl;


		send(clientSocket, buf, bytesReceived + 1, 0);
	
	}

	closesocket(clientSocket);

	WSACleanup();
}

