#pragma once
#include "SocketHandle.h"
#include "IPVersion.h"
#include "Result.h"
#include "SocketOption.h"
#include "Packet.h"
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

	Result Send(Packet & packet);
	Result Recv(Packet & packet);
	Result Send(const void * data, size_t numberOfBytes, size_t & bytesSent);
	Result Recv(void * dest, size_t numberOfBytes, size_t & bytesReceived);
	Result SendAll(const void * data, size_t numberOfBytes);
	Result RecvAll(void * dest, size_t numberOfBytes);

	IPVersion GetIPVersion();

private:
	Result SetSocketOpt(SocketOption option, BOOL val);
	IPVersion m_ipversion = IPVersion::IPv4;
	SocketHandle m_handle = INVALID_SOCKET;
};