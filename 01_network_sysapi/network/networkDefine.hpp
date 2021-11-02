#ifndef NETDEFINE_HPP
#define NETDEFINE_HPP

#include <cstdint>
#include <stdexcept>

#define MAX_CONNECTION 5

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN 
		#define WIN32_LEAN_AND_MEAN
	#endif // WIN32_LEAN_AND_MEAN
	
	#define _WIN32_WINNT_WIN10  0x0A00
	
	#include <winsock2.h>
	#include <WS2tcpip.h>

	#pragma comment(lib, "Ws2_32.lib")

#endif // _WIN32

namespace network {
	
#ifdef _WIN32
	typedef SOCKET socket_t;
	typedef SSIZE_T error_t;
	
	enum : error_t {
		MY_ERROR_SOCKET = SOCKET_ERROR,
		MY_INVALID_SOCKET = INVALID_SOCKET,
		MY_WSAENOTSOCK = WSAENOTSOCK
	};
	
	class NETWORK_INIT {
		WSADATA wsdata;
	public:
		NETWORK_INIT() {
			if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
				throw std::invalid_argument("ERROR! Call WSAStartup!");
			}
		}
		~NETWORK_INIT() { WSACleanup(); }
	};
	
#endif // _WIN32

#ifdef __linux__

#endif // __linux__

}

#endif // NETDEFINE_HPP
