#include <gl_networking/Includes.h>

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <sstream>


bool requestProcessed = true;
static MySocket newConnection = {};
std::map<int, std::string> processList = {};

void OutputList(const std::map<int, std::string> & processList)
{
	for(auto it = processList.begin(); it != processList.end(); it++)
	{
		std::cout << "PID: " << it->first << " " << "Process name: " << it->second << std::endl;
	}
}

bool SocketConnectionEstablishment(MySocket & socket, IPEndPoint ipPortData)
{
	
	if (socket.Create() == Result::Success)
	{
		std::cout << "Created successfully, socket options were set" << std::endl;
		

		if (socket.Listen(ipPortData) == Result::Success)
		{
			std::cout << "Listening on port: " << ipPortData.GetPort() << std::endl;
	
			if (socket.Accept(newConnection) == Result::Error)
			{
				std::cout << "Failed to accept new connection: " << ipPortData.GetIPString() << std::endl;
				return false;
			}
			else
			{
				std::cout << "Connected successfully to " << ipPortData.GetIPString() << " on port " << ipPortData.GetPort() << std::endl;
			}
		}
		else
		{
			std::cout << "Failed to listen on port: " << ipPortData.GetPort() << std::endl;
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void SocketClosing(MySocket & socket)
{
	socket.Close();
}

bool ProcessPacket(Packet & inputPacket)
{
	std::string response = " ";
	std::string processName = " ";
	uint32_t listSize = 0;
	uint32_t subListSize = 0;
	uint32_t PID = 0;
	switch (inputPacket.GetPacketType())
	{
	case PacketType::InvalidPacket:
		std::cout << "Error: Invalid Packet Type" << std::endl;
		return false;

	case PacketType::ProcessListResponsePacket:

		
		processList.clear();
		inputPacket >> listSize;
		for(int i = 0; i < listSize; i++)
		{
			int processID;
			std::string processName;
			inputPacket >> (uint32_t&)processID;
			inputPacket >> processName;
			processList[processID] = processName;
		}
		OutputList(processList);
		break;
	case PacketType::ProcessTerminatedResponsePacket:
		
		inputPacket >> response;
		std::cout << response << std::endl;
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
	std::string command = "";
	while (true)
	{
		if (requestProcessed)
		{
			std::cout << "Type command: ";
			std::getline(std::cin, command);

			if (command == "break")
			{
				std::cout << "Exiting..." << std::endl;
				break;
			}

			else if (command == "get list")
			{
				packet.Clear();
				packet.AssignPacketType(PacketType::ProcessListRequestPacket);
				if (newConnection.Send(packet) == Result::Error)
				{
					std::cout << "Failed to send request packet" << std::endl;
					break;
				}
				requestProcessed = false;

			}
			else if (command == "terminate")
			{
				
				if (!processList.empty())
				{
					std::string processName;
					std::cout << "Type Process Name to terminate: ";
					std::getline(std::cin, processName);
					packet.Clear();
					packet.AssignPacketType(PacketType::ProcessToTerminateRequestPacket);
					packet << processName;
					if (newConnection.Send(packet) == Result::Error)
					{
						std::cout << "Failed to send PID" << std::endl;
						break;
					}
					requestProcessed = false;
				}
				else
				{
					std::cout << "Process list is empty" << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "Unknown command" << std::endl;
				continue;
			}
		}
		
		std::cout << "In progress..." << std::endl;
		if (newConnection.Recv(packet) == Result::Error)
		{
			std::cout << "Failed to receive packet" << std::endl;
			break;
		}
	
		if (!ProcessPacket(packet))
		{
			std::cout << "Failed to process packet" << std::endl;
			break;
		}
		requestProcessed = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
	}

	SocketClosing(sock);
	Network::Shutdown();
	system("pause");
}
