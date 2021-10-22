#include "MessengerNetworking/tcp_client.h"
void tcpClient::bind(){
	hint.sin_family = AF_INET;
	hint.sin_port = htons(conPort);
    auto validate = inet_addr(ipAdress.c_str());
    if(validate == INADDR_NONE)
        {
            std::cerr << "Wrong ip" << std::endl;
            return;
        }
	hint.sin_addr.S_un.S_addr = validate;
}
void tcpClient::run(){
    connect();
}
void tcpClient::connect(){
    initializeWinsock();
    createSocket();
    bind();
    int connResult = ::connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
    char buf[4096];
	std::string userInput;
    do
	{
		std::cout << "> ";
		getline(std::cin, userInput);
		if (userInput.size() > 0)		
		{
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
			}
		}
	
	} while (userInput.size() > 0);
	closesocket(sock);
	WSACleanup();
}