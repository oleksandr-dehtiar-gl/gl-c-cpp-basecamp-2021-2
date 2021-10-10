#ifndef NETWORK_HPP
#define NETWORK_HPP

/* Define platform dependent macros by cmake 
	WIN32_API for Windows UNIX_API for Linux  
*/
#include <PlatformConfig.hpp>

// INCLUDE PLATFORM DEPENDENT HEADER FILES
// =======================================
#ifdef WIN32_API
	#ifndef WIN32_LEAN_AND_MEAN 
		#define WIN32_LEAN_AND_MEAN
	#endif // WIN32_LEAN_AND_MEAN
	
	#define _WIN32_WINNT 0x501
	
	#include <windows.h>

	#include <winsock2.h>
	#include <ws2tcpip.h>
	
	#ifdef MSVC
		#pragma comment(lib, "Ws2_32.lib")
	#endif // MSVC
#endif // WIN32_API

// TYPEDEF FOR TYPES AND DATA STRUCTURE
// ====================================
#ifdef WIN32_API

#endif // WIN32_API

#ifdef UNIX_API
	
#endif // WIN32_API

// NETWORK FUNCTION WRAPPERS
// =========================
#ifdef WIN32_API
	#define INIT() 	WSADATA wsdata; \
					if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) { \
						printf("Error call WSAStartup!\n"); \
						WSACleanup(); return 1;  \
					}
#endif // WIN32_API

namespace network {
	
	SOCKET tcp_server(char *hostname, char *servname);
}

#endif // NETWORK_HPP