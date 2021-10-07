#define UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include <gl_networking\Includes.h>

#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>


std::map<int, std::string> GetProcessList()
{
	HANDLE hndl = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
	if (hndl)
	{
		PROCESSENTRY32  process = { sizeof(PROCESSENTRY32) };
		Process32First(hndl, &process);
		std::map<int, std::string> processList;
		do
		{
			char ch[260];
			char DefChar = ' ';
			WideCharToMultiByte(CP_ACP, 0, process.szExeFile, -1, ch, 260, &DefChar, NULL);
			std::string processName(ch);
			processList[process.th32ProcessID] = processName;



		} while (Process32Next(hndl, &process));

		CloseHandle(hndl);
		return processList;
	}
	return std::map<int, std::string>();
}


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
	std::map<int, std::string> processList = {};
	uint32_t processId = 0;
	std::string processName = " ";
	size_t processListSize = 0;
	
	HANDLE Process;
	switch (inputPacket.GetPacketType())
	{
	case PacketType::InvalidPacket:
		std::cout << "Invalid Packet Type" << std::endl;
		return false;
	case PacketType::ProcessListRequestPacket:
		processList.clear();
		processList = GetProcessList();
		if (processList.empty())
		{
			inputPacket.Clear();
			inputPacket.AssignPacketType(PacketType::ProcessTerminatedResponsePacket);
			inputPacket << "Error Occured: unable to get process list\n";
			break;
		}
		processListSize = processList.size();
		inputPacket.Clear();
		inputPacket.AssignPacketType(PacketType::ProcessListResponsePacket);
		inputPacket << processListSize;
		for (auto entry = processList.begin(); entry != processList.end(); entry++)
		{
			inputPacket << entry->first << entry->second;
		}
		break;
	case PacketType::ProcessPairRequestPacket:

		inputPacket >> processId >> processName;

		Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		inputPacket.Clear();
		inputPacket.AssignPacketType(PacketType::ProcessTerminatedResponsePacket);
		if (!TerminateProcess(Process, 0))
		{
			inputPacket << "Failed to terminate process\n";
		}
		else
		{
			std::stringstream ss;
			ss << processId;
			inputPacket << "Process " + processName + "(pid: " + ss.str() + ")" + " was successfully terminated\n";
			inputPacket >> processName;
			std::cout << processName;
		}
		CloseHandle(Process);
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
		Sleep(500);
	}


	SocketClosing(sock);
	Network::Shutdown();
	system("pause");
}