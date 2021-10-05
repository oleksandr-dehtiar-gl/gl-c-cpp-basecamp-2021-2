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
	IPVersion GetIPVersion();

private:
	Result SetSocketOpt(SocketOption option, BOOL val);
	IPVersion m_ipversion = IPVersion::IPv4;
	SocketHandle m_handle = INVALID_SOCKET;
};