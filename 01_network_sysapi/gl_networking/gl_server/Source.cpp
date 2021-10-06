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