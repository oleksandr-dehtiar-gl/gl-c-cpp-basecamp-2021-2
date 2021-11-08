#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "network.hpp"

// #define DEBUG

namespace network {
	
	int getLastErr() {
		return WSAGetLastError();
	}
	
	int Write(socket_t s, const char* buf, unsigned int n) {
		return send(s, buf, n, 0);
	}
	
	int Writen(socket_t s, const char* buf, unsigned int n) {
		unsigned int leftToWrite = n;
		unsigned int alreadyWrite;
		const char *ptr = static_cast<const char*>(buf);

		while (leftToWrite > 0) {
			alreadyWrite = Write(s, ptr, leftToWrite);
			if ( alreadyWrite == 0) { 
				if (alreadyWrite != WSAEINTR) {
					break;
				}
			}
			leftToWrite -= alreadyWrite;
			ptr += alreadyWrite;
		}
		n = n - leftToWrite;
		return n;
	}
	
	int Read(socket_t s, char* buf, unsigned int n) {
		return recv(s, buf, n, 0);
	}
	
	int Readn(socket_t s, char* buf, unsigned int n) {
		unsigned int leftToRead = n;
		unsigned int alreadyRead;
		char *ptr = static_cast<char*>(buf);
		
		while (leftToRead > 0) {
			alreadyRead = Read(s, ptr, leftToRead);
			if (alreadyRead == 0) {
				if (alreadyRead != WSAEINTR) {
					break;
				}
			}
			leftToRead -= alreadyRead;
			ptr   += alreadyRead;
		}
		return n - leftToRead;
	}
	
	socket_t tcpListen(const char *host, const char *serv, int family) {
		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_family = family;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		
		guard_addrinfo ai(host, serv, &hints);
		socket_t Listensock;
		const int optVal = 1;
		int i = 0;
		for(; i < ai.size(); ++i) {
			Listensock = socket(ai.family(i), ai.socktype(i), ai.protocol(i));
			if (Listensock == MY_ERROR_SOCKET) 
				continue;
			setsockopt(Listensock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), sizeof(optVal));
			if (bind(Listensock, ai.addr(i), ai.addrlen(i)) != MY_ERROR_SOCKET)
				break;
			closesocket(Listensock);
		}
		if (i >= ai.size()) {
			fprintf(stderr, "ERROR! tcpListen!\n- invalid address: host %s serv %s\n", host, serv);
			return MY_ERROR_SOCKET;
		}
		if (listen(Listensock, MAX_CONNECTION) == MY_ERROR_SOCKET) {
			fprintf(stderr, "ERROR! tcpListen! host: %s serv: %s\n- ", host, serv);
			printErrorMessage(WSAGetLastError());
			return MY_ERROR_SOCKET;
		}
		ai.print();
		return Listensock;
	}
	
	socket_t tcpConnect(const char *host, const char *serv, int family) {
		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = family;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		
		guard_addrinfo ai(host, serv, &hints);
		socket_t connectSock;
		int i = 0;
		for(; i < ai.size(); ++i) {
			connectSock = socket(ai.family(i), ai.socktype(i), ai.protocol(i));
			if (connectSock == MY_ERROR_SOCKET) 
				continue;
			if (connect(connectSock, ai.addr(i), ai.addrlen(i)) != MY_ERROR_SOCKET)
				break;
			closesocket(connectSock);
		}
		if (i >= ai.size()) {
			fprintf(stderr, "ERROR NETWORK!\n-- error connect socket host: %s\n", host);
			return MY_ERROR_SOCKET;
		}
		ai.print();
		return connectSock;
	}
	
	void printErrorMessage(error_t codeID) {
		if(codeID == 0) 
			return;
		LPSTR messageBuffer = nullptr;
		// allocate memory that contain error message
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 NULL, codeID, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR)&messageBuffer, 0, NULL);
		fwrite(messageBuffer, sizeof(char), size, stderr);
		// Delete(free) string's buffer allocated by FormatMessageA function.
		LocalFree(messageBuffer);
	}
	
	uint16_t hostToNet_u16(uint16_t val) { return htons(val); }
	uint32_t hostToNet_u32(uint32_t val) { return htonl(val); }
	uint64_t hostToNet_u64(uint64_t val) { return htonll(val); }
	uint16_t netToHost_u16(uint16_t val) { return ntohs(val); }
	uint32_t netToHost_u32(uint32_t val) { return ntohl(val); }
	uint64_t netToHost_u64(uint64_t val) { return ntohll(val); }

}
