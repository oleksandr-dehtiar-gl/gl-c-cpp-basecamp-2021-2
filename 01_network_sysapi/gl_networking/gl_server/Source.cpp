#include <gl_networking\Includes.h>

#include <iostream>

int main()
{
	

	
	if (Network::Initialize())
	{
		std::cout << "Initialized" << std::endl;
	}

	IPEndPoint endpoint("127.0.0.1", 8080);
	MySocket sock;
	
	if (sock.Create() == Result::Success)
	{
		std::cout << "Created successfully, socket options were set" << std::endl;
		
		if (sock.Listen(endpoint) == Result::Success)
		{
			std::cout << "Socket listens on port 8080 " << std::endl;
			MySocket newConnection;
			if (sock.Accept(newConnection) == Result::Success)
			{
				std::cout << "Connection established" << std::endl;
			}
			else
			{
				std::cout << "Failed to connect..." << std::endl;
			}
			while (true)
			{
				char buff[256];
				size_t bytesReceived = 0;
				if (newConnection.Recv(buff, 256, bytesReceived) == Result::Error)
				{
					std::cerr << "Failed to receive message..." << std::endl;
					break;
				}
				std::cout << buff;
				Sleep(500);
			}
		}
		else
		{
			std::cout << "Failed to listen on port 8080 " << std::endl;
		}
		
	}
	sock.Close();
	Network::Shutdown();
	system("pause");
}