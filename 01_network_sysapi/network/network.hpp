#ifndef NETAPI_HPP
#define NETAPI_HPP

#include "networkDefine.hpp"
#include "guardAddrinfo.hpp"
#include "mySocket.hpp"

namespace network {
	
	socket_t tcpConnect(const char *host, const char *serv, int family);
	socket_t tcpListen(const char *host, const char *serv, int family);
	void printErrorMessage(error_t codeID);

	int Write(socket_t s, const char* buf, unsigned int n);
	int Writen(socket_t s, const char* buf, unsigned int n);
	int Read(socket_t s, char* buf, unsigned int n);
	int Readn(socket_t s, char* buf, unsigned int n);
	
	int getLastErr();
	
	uint16_t hostToNet_u16(uint16_t val);
	uint32_t hostToNet_u32(uint32_t val);
	uint64_t hostToNet_u64(uint64_t val);
	uint16_t netToHost_u16(uint16_t val);
	uint32_t netToHost_u32(uint32_t val);
	uint64_t netToHost_u64(uint64_t val);
}

#endif // NETAPI_HPP

