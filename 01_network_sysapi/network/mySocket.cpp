#include "mySocket.hpp"

namespace network {
	
	int mySocket::shutdownWrite() {
		return shutdown(mSocket, SD_SEND);
	}
	
	void mySocket::sockIsValid(SOCKET s) {
		int error_code = 0;
		int error_code_size = sizeof(int);
		if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&error_code, &error_code_size) == MY_ERROR_SOCKET) {
			if (getLastErr() == MY_WSAENOTSOCK)
				printf("ERROR! Socket dosn't exist\n");
			throw std::invalid_argument("Cannot create mySocket!\n");
		}
	}
	
	mySocket::mySocket(SOCKET &&s, const sockaddr *name, int namelen)
		: mSocket(MY_INVALID_SOCKET)
	{
		sockIsValid(s);
		std::swap(s, mSocket);
		if (connect(mSocket, name, namelen) == MY_ERROR_SOCKET) {
			closesocket(mSocket);
			throw std::logic_error("Unable to connect to server!\n");
		}
	}
	
	mySocket::mySocket(SOCKET &&s) 
		: mSocket(MY_INVALID_SOCKET) 
	{
		sockIsValid(s);
		std::swap(s, mSocket);
	}
	
	void mySocket::swap(mySocket &s) {
		std::swap(s.mSocket, mSocket);
	}
	
	mySocket::mySocket(mySocket &&s)
		: mSocket(MY_INVALID_SOCKET) 
	{
		std::swap(s.mSocket, mSocket);
	}
	
	int mySocket::write(const char* data, int n) {
		return Write(mSocket, data, n);
	}
	
	int mySocket::writen(const char* data, int n) {
		return Writen(mSocket, data, n);
	}
	
	int mySocket::read(char* data, int n) {
		return Read(mSocket, data, n);
	}
	
	int mySocket::readn(char* data, int n) {
		return Readn(mSocket, data, n);
	}
	
}
