#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "netApi.hpp"

namespace network {
	
	socket_t tcpListen(char *hostname, char *servname) {
			
		struct addrinfo *result = nullptr, *copyResult = nullptr, hints;
		
		memset(&hints, 0, sizeof(hints));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		
		if (getaddrinfo(hostname, servname, &hints, &result) != 0) {
			fprintf(stderr, "ERROR tcpListen! hostname: %s servname: %s\n-- ", hostname, servname);
			printErrorMessage(WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
		copyResult=result;
		
		socket_t Listensock;
		const int optVal = 1;
		do {
			Listensock = socket(copyResult->ai_family, copyResult->ai_socktype, copyResult->ai_protocol);
			if (!socetkIsValid(Listensock)) 
				continue;
				
			setsockopt(Listensock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), sizeof(optVal));
			if (bind(Listensock, copyResult->ai_addr, copyResult->ai_addrlen) != SOCKET_ERROR)
				break;
				
			closesocket(Listensock);
			
		} while ((copyResult = copyResult->ai_next) != nullptr);
		
		if (copyResult == nullptr) {
			fprintf(stderr, "ERROR tcpListen!\n-- error listen socket on this hostname: %s servname: %s", hostname, servname);
			exit(EXIT_FAILURE);
		}
		
		if (listen(Listensock, MAX_CONNECTION) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR tcpListen! hostname: %s servname: %s\n-- ", hostname, servname);
			printErrorMessage(WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
		freeaddrinfo(result);
		
		return Listensock;
	}
	
	socket_t tcpConnect(char *hostname, char *servname) {
		
		struct addrinfo *result = nullptr, *copyResult = nullptr, hints;
		
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		
		if (getaddrinfo(hostname, servname, &hints, &result) != 0) {
			fprintf(stderr, "ERROR tcpConnect! hostname: %s servname: %s\n-- ", hostname, servname);
			printErrorMessage(WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
		copyResult=result;
		socket_t connectSock;
		do {
			connectSock = socket(copyResult->ai_family, copyResult->ai_socktype, copyResult->ai_protocol);
			if (!socetkIsValid(connectSock)) 
				continue;

			if (connect(connectSock, copyResult->ai_addr, copyResult->ai_addrlen) != SOCKET_ERROR)
				break;
				
			closesocket(connectSock);
			
		} while ((copyResult = copyResult->ai_next) != nullptr);
		
		if (copyResult == nullptr) {
			fprintf(stderr, "ERROR NETWORK!\n-- error connect socket on this hostname: %s", hostname);
			exit(EXIT_FAILURE);
		}

		freeaddrinfo(result);
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
	
	socket_t Accept(socket_t s) { return accept(s, NULL, NULL); }
	
	error_t getLastSocketError() { return WSAGetLastError(); }
	
	bool socetkIsValid(socket_t s) { return s == INVALID_SOCKET ? false : true; }
		
	//error_t getPeerName(socket_t s, SA *name, int *namelen) { return getpeername(s, name, namelen); }
	
	error_t Read(socket_t s, void *vptr, unsigned int *n) {
		unsigned int readnum = recv(s, static_cast<char*>(vptr), *n, 0);
		if (readnum == SOCKET_ERROR) {
			printf("SOCKET ERROR\n");
			*n = 0;
			return getLastSocketError();
		} else if (readnum == 0) {
			printf("SUCCESS CLOSED: n = %d\n", *n);
			*n = 0;
			return 0;
		}
		*n = readnum;
		return 0; // return zero if no error ocure
	}
	
	error_t Readn(socket_t s, void *vptr, unsigned int *n) {
		unsigned int leftToRead = *n;
		unsigned int alreadyRead;
		char *ptr = static_cast<char*>(vptr);
		
		error_t curError;
		while (leftToRead > 0) {
			alreadyRead = leftToRead;
			curError = Read(s, ptr, &alreadyRead);
			if (curError == 0) {
				if ( alreadyRead == 0) {
					break;
				}
			} else {
				if (curError != WSAEINTR) {
					break;
				}
			}
			leftToRead -= alreadyRead;
			ptr   += alreadyRead;
		}
		*n = *n - leftToRead;
		return curError;
	}
	
	error_t Write(socket_t s, const void *cvptr, unsigned int *n) {
		unsigned int sendCount = send(s, static_cast<const char*>(cvptr), *n, 0);
		if (sendCount == SOCKET_ERROR) {
			*n = 0; // no data has been send
			return getLastSocketError();
		}
		*n = sendCount;
		return 0;
	}
	
	error_t Writen(socket_t s, const void *cvptr, unsigned int *n) {
		unsigned int leftToWrite = *n;
		unsigned int alreadyWrite;
		const char *ptr = static_cast<const char*>(cvptr);

		error_t curError;
		while (leftToWrite > 0) {
			alreadyWrite = leftToWrite;
			curError = Write(s, ptr, &alreadyWrite);
			if ( alreadyWrite == 0) { 
				if (curError != WSAEINTR) {
					*n = *n - leftToWrite;
					return curError;
				}
			}
			leftToWrite -= alreadyWrite;
			ptr += alreadyWrite;
		}
		*n = *n - leftToWrite;
		return 0;
	}
	
	error_t Shutdown(socket_t s, SHDWN how) {
		return shutdown(s, how) == SOCKET_ERROR ? getLastSocketError() : 0;
	}

	error_t closesocket(socket_t s) {
		if (SOCKET_ERROR == closesocket(s))
			return getLastSocketError();
		return 0;
	}
}
