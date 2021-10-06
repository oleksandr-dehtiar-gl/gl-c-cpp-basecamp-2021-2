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