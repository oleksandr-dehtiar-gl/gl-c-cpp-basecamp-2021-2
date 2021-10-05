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
		std::cout << "Created successfully? socket options were set" << std::endl;
	}
	sock.Close();
	Network::Shutdown();
	system("pause");
}