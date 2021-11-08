#ifndef MYSOCKET_HPP
#define MYSOCKET_HPP

#include "network.hpp"

namespace network {
	
	class mySocket {
		socket_t mSocket;
	private:
		void sockIsValid(socket_t s);
	public:
		mySocket(mySocket&) = delete;
		mySocket& operator=(mySocket&) = delete;
	public:
		mySocket(socket_t &&s, const sockaddr *name, int namelen);
		explicit mySocket(mySocket &&s);
		explicit mySocket(socket_t &&s);
		void swap(mySocket &s);
	public:
		~mySocket() { if (mSocket != MY_INVALID_SOCKET) closesocket(mSocket); }
	public:
		int write(const char* data, int n);
		int writen(const char* data, int n);
		int read(char* data, int n);
		int readn(char* data, int n);
		int shutdownWrite();
	};
	
}

#endif // MYSOCKET_HPP
