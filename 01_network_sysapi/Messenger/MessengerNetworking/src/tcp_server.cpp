#include "MessengerNetworking/tcp_server.h"
void tcpServer::bind(){
	hint.sin_family = AF_INET;
	hint.sin_port = htons(conPort);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(sock, (sockaddr*)&hint, sizeof(hint));
}
void tcpServer::bind(SOCKET sock){
	hint.sin_family = AF_INET;
	hint.sin_port = htons(conPort);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(sock, (sockaddr*)&hint, sizeof(hint));
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
	std::string serverInput="";	
	std::string msgRecv = "";
	while (true)
	{
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
			throw new std::exception("Error in recv(). Quitting.");
		if (bytesReceived == 0)
			throw new std::exception("Client disconnected.");
		msgRecv = std::string(buf, 0, bytesReceived);
		std::cout << host << "> "<< msgRecv << std::endl;
		if(IsCommandRight(serverInput) && msgRecv == "success"){
			conPort = std::stoi(serverInput.substr(8, serverInput.size()-1));
			bind(clientSocket);
		}
		std::cout << "> ";
		if(IsCommandRight(msgRecv)){
			conPort = std::stoi(msgRecv.substr(8, msgRecv.size()-1));
			bind(clientSocket);
			serverInput = "success";
			std::cout << serverInput << std::endl;
			int sendResult = send(clientSocket, serverInput.c_str(), serverInput.size() + 1, 0);
		}
		else
		{
		getline(std::cin, serverInput);
		if (serverInput.size() > 0)		
			int sendResult = send(clientSocket, serverInput.c_str(), serverInput.size() + 1, 0);
		}
	}
	disconnect(clientSocket);
}

void tcpServer::disconnect(SOCKET sock){
	    closesocket(sock);
		WSACleanup();
}