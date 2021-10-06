#pragma once
#include "SocketHandle.h"
#include "IPVersion.h"
#include "Result.h"
#include "SocketOption.h"
class MySocket
{
public:


	MySocket(IPVersion version = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);
	Result Create();
	Result Close();
	SocketHandle GetSocketHandle();
	Result Bind(IPEndPoint endpoint);
	Result Listen(IPEndPoint endpoint, int backlog = 3);
	Result Accept(MySocket & socketToAccept);
	Result Connect(IPEndPoint endpoint);
	Result Send(const void * data, size_t numberOfBytes, size_t & bytesSent);
	Result Recv(void * dest, size_t numberOfBytes, size_t & bytesReceived);
	IPVersion GetIPVersion();

private:
	Result SetSocketOpt(SocketOption option, BOOL val);
	IPVersion m_ipversion = IPVersion::IPv4;
	SocketHandle m_handle = INVALID_SOCKET;
};