#include "IPEndPoint.h"
#include <cstring>
#include "WinToUNIXtypedefs.h"
IPEndPoint::IPEndPoint(const char * ip, unsigned short port)
{
	m_port = port;
	in_addr addr;
	int result = inet_pton(AF_INET, ip, &addr); 

	if (result == 1)
	{
		if (addr.s_addr != INADDR_NONE)
		{
			m_ip_string = ip;
			m_host_name = ip;
			m_version = IPVersion::IPv4;

			m_bytes.resize(sizeof(ULONG));
			memcpy(m_bytes.data(), &addr.s_addr, sizeof(ULONG));

		}
	}

	
}

sockaddr_in IPEndPoint::GetAddrIPv4()
{
	sockaddr_in addr = {};

	memcpy(&addr.sin_addr, m_bytes.data(), sizeof(ULONG));

	addr.sin_port = htons(m_port);
	addr.sin_family = AF_INET;

	return addr;

}

std::string IPEndPoint::GetHostName() const
{
	return m_host_name;
}

std::string IPEndPoint::GetIPString() const
{
	return m_ip_string;
}

std::vector<uint8_t> IPEndPoint::GetByteVector() const
{
	return m_bytes;
}
unsigned short IPEndPoint::GetPort() const
{
	return m_port;
}

IPVersion IPEndPoint::GetVersion() const
{
	return m_version;
}
