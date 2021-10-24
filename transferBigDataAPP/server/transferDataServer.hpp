#ifndef TRANSFERDATACLIENT_HPP
#define TRANSFERDATACLIENT_HPP

#include <string>
#include <memory>
#include <fstream>

#include <threadSafeQueue.hpp>
#include <connection.hpp>
#include <packet.hpp>

#define SIZE_PACKE_BUF 4096

namespace transferApp {
	
	class ExceptionTtransferDataServer : public std::exception {
	public:
		ExceptionTtransferDataServer(std::string &msg) : std::exception(("ExceptionTtransferDataServer::" + msg).c_str()) {}
	};
	
	class TtransferDataServer {
	private:
		struct PackFile {
			size_t size;
			char buf[SIZE_PACKE_BUF];
			PackFile() { size = 4096; }
		};
	private:
		SocketConnection mConnection;
		ThreadSafeQueue<PackFile> mSafeQueue;
		std::atomic<bool> mStopReadSock;
		std::ofstream mFout; 
		std::filebuf* mFoutbuf;
	public:
		TtransferDataServer(const TtransferDataServer &) = delete;
		TtransferDataServer& operator=(const TtransferDataServer &) = delete;
	public:
		TtransferDataServer(const char *hostname, const char *servname);
		TtransferDataServer(SocketConnection &&connection);
	private:
		void init(std::string ermsg);
		void send();
		void receive();
		void processData();
		std::string showAndSelectFile();
	public:
		void run();
	};

}

#endif // TRANSFERDATACLIENT_HPP
