#ifndef NETWORK_HPP
#define NETWORK_HPP

// INCLUDE PLATFORM DEPENDENT HEADER FILES
// =======================================
#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN 
		#define WIN32_LEAN_AND_MEAN
	#endif // WIN32_LEAN_AND_MEAN
	
	#define _WIN32_WINNT 0x501
	
	#include <windows.h>

	#include <winsock2.h>
	#include <ws2tcpip.h>
	
	#ifdef _MSC_VER
		#pragma comment(lib, "Ws2_32.lib")
	#endif // _MSC_VER
#endif // _WIN32

// TYPEDEF FOR TYPES AND DATA STRUCTURE
// ====================================
#ifdef _WIN32

#endif // _WIN32

#ifdef __linux__
	
#endif // _WIN32

// NETWORK FUNCTION WRAPPERS
// =========================
#ifdef _WIN32
	#define INIT() 	WSADATA wsdata; \
					if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) { \
						printf("Error call WSAStartup!\n"); \
						WSACleanup(); return 1;  \
					}
#endif // _WIN32

namespace network {
	
	SOCKET tcp_server(char *hostname, char *servname);
}

#endif // NETWORK_HPP
