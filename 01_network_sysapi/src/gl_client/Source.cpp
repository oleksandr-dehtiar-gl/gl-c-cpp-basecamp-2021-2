

#include <gl_networking/Includes.h>
#include <gl_sysapi/ProcessManager.h>
#include <thread>
#include <chrono>
#include <sstream>
std::map<int, std::string>  processList;

bool SocketConnectionEstablishment(MySocket & socket, IPEndPoint ipPortData)
{
	if (socket.Create() == Result::Success)
	{
		std::cout << "Created successfully, socket options were set" << std::endl;

		if (socket.Connect(ipPortData) == Result::Success)
		{
			std::cout << "Connection established on ip: " << ipPortData.GetIPString() << " and port: " << ipPortData.GetPort() << std::endl;
			return true;
		}
		else
		{
			std::cout << "Failed to connect ip: " << ipPortData.GetIPString() << " and port: " << ipPortData.GetPort() << std::endl;
			return false;
		}
	}
	return false;
}

void SocketClosing(MySocket & socket)
{
	socket.Close();
}

bool ProcessPacket(Packet & inputPacket)
{

	uint32_t processId = 0;
	std::string processName = " ";
	size_t processListSize = 0;



	switch (inputPacket.GetPacketType())
	{
	case PacketType::InvalidPacket:
		std::cout << "Invalid Packet Type" << std::endl;
		return false;
	case PacketType::ProcessListRequestPacket:

		inputPacket.Clear();
		inputPacket.AssignPacketType(PacketType::ProcessListResponsePacket);

		if (ProcessManager::GetProcessList().empty())
		{
			inputPacket.Clear();
			inputPacket.AssignPacketType(PacketType::ProcessTerminatedResponsePacket);
			inputPacket << "Error Occured: unable to get process list\n";
			break;
		}
		processList = ProcessManager::GetProcessList(false);

		inputPacket << processList.size();
		for(auto it = processList.begin(); it != processList.end(); it++)
		{
			std::cout << "PID: " << it->first << " " << "Process name: " << it->second << std::endl;
			inputPacket << it->first << it->second;
		}
		break;
	case PacketType::ProcessToTerminateRequestPacket:

		inputPacket >> processName;


		inputPacket.Clear();
		inputPacket.AssignPacketType(PacketType::ProcessTerminatedResponsePacket);

		if (!ProcessManager::TerminateProcess(processName))
		{
			inputPacket << "Failed to terminate process\n";
		}
		else
		{
	
			inputPacket << processName + " terminated\n";

		}

		break;
	default:
		return false;
	}
	return true;
}


int main()
{
	if (Network::Initialize())
	{
		std::cout << "Initialized" << std::endl;
	}

	IPEndPoint endpoint("127.0.0.1", 4790);
	MySocket sock;
	if (!SocketConnectionEstablishment(sock, endpoint))
	{
		return 1;
	}
	Packet packet;

	std::string command;

	while (true)
	{

		std::cout << "Waiting for request" << std::endl;
		if (sock.Recv(packet) != Result::Success)
		{
			std::cout << "Failed to receive packet." << std::endl;
			break;
		}
		else
		{
			if (!ProcessPacket(packet))
			{
				std::cout << "Failed to process packet." << std::endl;
				break;
			}
			if (sock.Send(packet) != Result::Success)
			{
				std::cout << "Failed to send response." << std::endl;
				break;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}


	SocketClosing(sock);
	Network::Shutdown();
	system("pause");
}
