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
		result = setsockopt(m_handle, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&val), sizeof(val));
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