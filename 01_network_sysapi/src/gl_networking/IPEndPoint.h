#pragma once
#include "IPVersion.h"

#ifdef _WIN32
#include <WS2tcpip.h>
#else 
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

#include <string>
#include <vector>
class IPEndPoint
{
public:
	IPEndPoint(const char *ip, unsigned short port);
	
	std::string GetHostName() const;
	std::string GetIPString() const;
	std::vector<uint8_t> GetByteVector() const;
	unsigned short GetPort() const;
	IPVersion GetVersion() const;
	sockaddr_in GetAddrIPv4();
	
private:
	std::string m_host_name = "";
	std::string m_ip_string = "";
	std::vector<uint8_t> m_bytes;
	unsigned short m_port;
	IPVersion m_version;
};
