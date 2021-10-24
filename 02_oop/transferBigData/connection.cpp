#include <iostream>
#include <exception>

#include "connection.hpp"

namespace transferApp {

	SocketConnection::SocketConnection(network::socket_t &&s) 
	: mSocket(s), mErrorVal(0) 
	{
	}
	
	SocketConnection::SocketConnection(SocketConnection &&copy) noexcept : 
		mSocket(network::ERROR_SOCK::FAIL_SOCKET),
		mErrorVal(0)
	{
		std::swap(mSocket, copy.mSocket);
		std::swap(mErrorVal, copy.mErrorVal);
	}
	
	unsigned int SocketConnection::read(char *buf, unsigned int n) {
		unsigned int readCount = n; 
		mErrorVal = network::Read(mSocket, buf, &readCount);
		// ... handle error
		return readCount;
	}
	
	unsigned int SocketConnection::readn(char *buf, unsigned int n) {
		unsigned int readCount = n; 
		mErrorVal = network::Readn(mSocket, buf, &readCount);
		// ... handle error
		return readCount;
	}

	unsigned int SocketConnection::write(const char *buf, unsigned int n) {
		unsigned int readCount = n; 
		mErrorVal = network::Write(mSocket, buf, &readCount);
		// ... handle error
		return readCount;
	}
	
	unsigned int SocketConnection::writen(const char *buf, unsigned int n) {
		unsigned int readCount = n; 
		mErrorVal = network::Writen(mSocket, buf, &readCount);
		// ... handle error
		return readCount;
	}

}
