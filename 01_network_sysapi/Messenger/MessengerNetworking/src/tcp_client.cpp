#include "MessengerNetworking/tcp_client.h"
void tcpClient::bind(){
	hint.sin_family = AF_INET;
	hint.sin_port = htons(conPort);
    auto validate = inet_addr(ipAdress.c_str());
	
    if(validate == INADDR_NONE)
            throw new std::exception("IP validation has failed.");
	hint.sin_addr.S_un.S_addr = validate;
}
void tcpClient::connect(){
    initializeWinsock();
    createSocket();
    bind();
    int connResult = ::connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
		throw new std::exception(("Can't connect to server, Err #" + std::to_string(WSAGetLastError())).c_str());
    char buf[4096];
	std::string userInput="";
	std::string msgRecv = "";
    do
	{
		std::cout << "> ";
		if(IsCommandRight(msgRecv)){
			conPort = std::stoi(msgRecv.substr(8, msgRecv.size()-1));
			bind();
			userInput = "success";
			std::cout << userInput << std::endl;
		}
		else
			getline(std::cin, userInput);	
		if (userInput.size() > 0)		
		{
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				msgRecv = std::string(buf, 0, bytesReceived);
				std::cout << "SERVER> " << msgRecv << std::endl;
				if(msgRecv == "success" && IsCommandRight(userInput))
				{
					conPort = std::stoi(userInput.substr(8, userInput.size()-1));
					bind();
				}
			}
			else
				throw new std::exception("Can't send message to the server.");
		}
	
	} while (userInput.size() > 0);
	disconnect();
}