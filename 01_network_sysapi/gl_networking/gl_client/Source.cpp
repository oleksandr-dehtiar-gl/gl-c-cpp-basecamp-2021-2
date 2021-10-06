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
			char buff[256];
			
			strcpy_s(buff, "First message\n");
			int bytesSent = 0;
			while (true)
			{
				if (sock.Send(buff, 256, (size_t&)bytesSent) != Result::Success)
				{
					std::cout << "Failed to send message\n" << std::endl;
					break;
				}
				std::cout << "Message sent" << std::endl;
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