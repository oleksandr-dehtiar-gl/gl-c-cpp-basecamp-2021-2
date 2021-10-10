#ifndef WINNETAPI_HPP
#define WINNETAPI_HPP

#include <cstdio>
#include <cstring>

#include "netApi.hpp"

namespace network {
	
	SOCKET tcp_server(char *hostname, char *servname) {
		struct addrinfo *result = NULL, *ptr = NULL, hints;

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		
		int status = getaddrinfo(hostname, servname, &hints, &result);
		if (status != 0) {
			printf("Error at getaddrinfo(): %ld\n", WSAGetLastError());
			return INVALID_SOCKET;
		}
		
		ptr=result;
		
		SOCKET ListenSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			return INVALID_SOCKET;
		}
		
		status = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (status == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			return INVALID_SOCKET;
		}
		freeaddrinfo(result);
		
		if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
			printf( "Listen failed with error: %ld\n", WSAGetLastError() );
			closesocket(ListenSocket);
			return INVALID_SOCKET;
		}
		
		return ListenSocket;
	}
	
}

#endif // WINNETAPI_HPP
