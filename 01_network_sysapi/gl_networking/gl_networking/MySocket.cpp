#include "MySocket.h"
#include <iostream>

MySocket::MySocket(IPVersion version, SocketHandle handle) : m_ipversion(version), m_handle(handle)
{}


Result MySocket::SetSocketOpt(SocketOption opt, BOOL val)
{
	int result = 0;
	switch (opt)
	{
	case SocketOption::TCP_NoDelay:
		result = setsockopt(m_handle, IPPROTO_TCP, TCP_NODELAY, (const char*)(&val), sizeof(val));
		break;

	default:
		return Result::Error;
	}
	if (result != 0)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;
	}
	return Result::Success;
}

Result MySocket::Create()
{
	if (m_handle != INVALID_SOCKET)
	{
		return Result::Error;
	}
	m_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_handle == INVALID_SOCKET)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;
	}
	if (SetSocketOpt(SocketOption::TCP_NoDelay, TRUE) == Result::Error)
	{
		return Result::Error;
	}
	return Result::Success;
}

Result MySocket::Connect(IPEndPoint endpoint)
{
	int result = connect(m_handle, (sockaddr*)(&endpoint.GetAddrIPv4()), sizeof(sockaddr));

	if (result != 0)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;
	}
	return Result::Success;
}



Result MySocket::Recv(void * data, size_t numberOfBytes, size_t & bytesReceived)
{
	bytesReceived = recv(m_handle, (char*)data, numberOfBytes, 0);

	if (bytesReceived == 0)
	{
		std::cerr << "Connection closed " << std::endl;
		return Result::Error;
	}
	if (bytesReceived == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;
	}
	return Result::Success;
}

Result MySocket::Send(const void * data, size_t numberOfBytes, size_t & bytesSent)
{
	bytesSent = send(m_handle, (const char*)data, numberOfBytes, 0);

	if (bytesSent == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;

		return Result::Error;
	}
	return Result::Success;

}

Result MySocket::Accept(MySocket & socketToAccept)
{
	SocketHandle newSocket;
	newSocket = accept(m_handle, nullptr, nullptr);
	if (newSocket == INVALID_SOCKET)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;
	}
	
	socketToAccept = MySocket(IPVersion::IPv4, newSocket);
	return Result::Success;


}


Result MySocket::Listen(IPEndPoint endpoint, int backlog)
{
	
	if (Bind(endpoint) == Result::Error)
	{
		return Result::Error;
	}
	int result = listen(m_handle, backlog);

	if (result != 0)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;
	}
	return Result::Success;

}

Result MySocket::Bind(IPEndPoint  endpoint)
{
	sockaddr_in addr = endpoint.GetAddrIPv4();
	int result = bind(m_handle, (sockaddr*)&addr, sizeof(sockaddr_in));

	if (result != 0)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;

		return Result::Error;

	}
	return Result::Success;
}

Result MySocket::Close()
{
	if (m_handle == INVALID_SOCKET)
	{
		return Result::Error;
	}
	int result = closesocket(m_handle);
	if (result != 0)
	{
		int err = WSAGetLastError();
		std::cerr << "Error code: " << err << std::endl;
		return Result::Error;

	}
	m_handle = INVALID_SOCKET;
	return Result::Success;
}

IPVersion MySocket::GetIPVersion()
{
	return m_ipversion;
}

SocketHandle MySocket::GetSocketHandle()
{
	return m_handle;
}