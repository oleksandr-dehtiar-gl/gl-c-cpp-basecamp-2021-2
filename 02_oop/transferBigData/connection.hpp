#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <fstream>
#include <iomanip>
#include <utility>
#include <exception>

#include <netApi.hpp>

namespace transferApp {
	

	class SocketConnection {
	private:
		network::socket_t mSocket;
		network::error_t mErrorVal;
	public:
		SocketConnection(const SocketConnection&) = delete;
		SocketConnection& operator=(const SocketConnection&) = delete;	
	public:
		SocketConnection() : mSocket(network::ERROR_SOCK::FAIL_SOCKET), mErrorVal(0) { }
		explicit SocketConnection(network::socket_t &&s);
		SocketConnection(SocketConnection &&copy) noexcept;
	public:
		inline network::error_t getErrorCode() { return mErrorVal; }
		inline bool connectIsValid() { return network::socetkIsValid(mSocket) ? true : false; }
	public:
		unsigned int read(char *buf, unsigned int n);
		unsigned int readn(char *buf, unsigned int n);
		unsigned int write(const char *buf, unsigned int n);
		unsigned int writen(const char *buf, unsigned int n);
	public:
		network::error_t shutdownRead() { return network::Shutdown(mSocket, network::SHUTDOWN::RECEIVE); }
		network::error_t shutdownWrite() { return network::Shutdown(mSocket, network::SHUTDOWN::SEND); }
		network::error_t shutdownReadWrite() { return network::Shutdown(mSocket, network::SHUTDOWN::BOTH); }

		~SocketConnection() { if(network::socetkIsValid(mSocket)) network::socketClose(mSocket); }
	};
	
}

#endif // CONNECTION_HPP
