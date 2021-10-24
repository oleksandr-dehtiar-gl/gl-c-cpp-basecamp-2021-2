#ifndef TRANSFERDATACLIENT_HPP
#define TRANSFERDATACLIENT_HPP

#include <string>
#include <memory>
#include <fstream>

#include <threadSafeQueue.hpp>
#include <connection.hpp>
#include <packet.hpp>
#include <transferUtility.hpp>

#define SIZE_PACKE_BUF 4096

namespace transferApp {
	
	class ExceptionTtransferDataClient : public std::exception {
	public:
		ExceptionTtransferDataClient(std::string &msg) : std::exception(("ExceptionTtransferDataClient::" + msg).c_str()) {}
	};
	
	class TtransferDataClient {
	private:
		struct PackFile {
			size_t size;
			char buf[SIZE_PACKE_BUF];
			PackFile() { size = 4096; }
		};
	private:
		SocketConnection mConnection;
		ThreadSafeQueue<PackFile> mSafeQueue;
		std::vector<transferApp::NameSize_p> mFileList;
		std::atomic<bool> mStopRedingFile;
		std::ifstream mFin;
		std::filebuf *mFinbuf;
	public:
		TtransferDataClient(const TtransferDataClient &) = delete;
		TtransferDataClient& operator=(const TtransferDataClient &) = delete;
	public:
		TtransferDataClient(const char *hostname, const char *servname);
		TtransferDataClient(SocketConnection &&connection);
	private:
		void init(std::string ermsg);
		void send();
		void receive();
		void prepareData();
		void sendFileList();
	public:
		void run();
	};

}

#endif // TRANSFERDATACLIENT_HPP
