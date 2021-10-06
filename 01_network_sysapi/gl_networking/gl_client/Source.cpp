#include <gl_networking\Includes.h>
#include <iostream>
int main()
{

	if (Network::Initialize())
	{
		std::cout << "Ok" << std::endl;
	}
	MySocket sock;
	if (sock.Create() == Result::Success)
	{
		std::cout << "Created successfully, socket options were set" << std::endl;
		if (sock.Connect(IPEndPoint("127.0.0.1", 8080)) ==  Result::Success)
		{
			std::cout << "Connection established " << std::endl;
			Packet dataPacket;
			int a = 4;
			int b = 6;
			int c = 2;
			dataPacket << a << b << c;
			while (true)
			{
				if (sock.Send(dataPacket) == Result::Error)
				{
					std::cout << "Failed to send packet" << std::endl;
					break;
				}

				std::cout << "Sending packet..." << std::endl;
				Sleep(500);
			}


		}
		else
		{
			std::cout << "Failed to connect " << std::endl;
		}
	}
	sock.Close();
	Network::Shutdown();
	system("pause");
}