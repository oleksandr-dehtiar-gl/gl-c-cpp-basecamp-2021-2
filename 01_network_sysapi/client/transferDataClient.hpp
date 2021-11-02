#ifndef TRANSFERDATACLIENT_HPP
#define TRANSFERDATACLIENT_HPP

#include <vector>
#include <string>
#include <utility>
#include <fstream>

#include <network.hpp>
#include <transferUtiltiy.hpp>
#include <threadSafeQueue.hpp>
#include <threadGuard.hpp>

#define SIZE_PACKE_BUF 1024

namespace transfer {
	
	class TransferDataClient {
	private:
		struct DataPacket { 
			size_t size;
			char data[SIZE_PACKE_BUF];
		};
	private:
		network::mySocket mSocket;
		std::vector<nameSize_p> mFileSizeList;
		ThreadSafeQueue<DataPacket> mSafeQueue;
		std::atomic<bool> mStopRedingFile;
	public:
		TransferDataClient(TransferDataClient &) = delete;
		TransferDataClient& operator=(TransferDataClient &) = delete;
	public:
		TransferDataClient(network::socket_t &&s);
	private:
		bool receiveAskFileServer();
		void sendFileList();
		nameSize_p getFileInfoFromServer();
		void readFromFile(std::ifstream &fin);
		void sendFileToServer(); 
	public:
		void run();
	};
	
}

#endif // TRANSFERDATACLIENT_HPP
