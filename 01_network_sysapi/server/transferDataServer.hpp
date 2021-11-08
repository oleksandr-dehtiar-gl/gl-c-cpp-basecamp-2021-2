#ifndef TRANSFERDATASERVER_HPP
#define TRANSFERDATASERVER_HPP

#include <map>
#include <string>
#include <utility>
#include <fstream>

#include <network.hpp>
#include <header.hpp>
#include <transferUtiltiy.hpp>
#include <threadSafeQueue.hpp>
#include <threadGuard.hpp>

#define SIZE_PACKE_BUF 1024

namespace transfer {
	
	class TransferDataServer {
	private:
		struct DataPacket { 
			size_t size;
			char data[SIZE_PACKE_BUF];
		};
	private:
		network::mySocket mSocket;
		nameSize_p mFileInfo;
		ThreadSafeQueue<DataPacket> mSafeQueue;
		std::atomic<bool> mStopReadSock;
	public:
		TransferDataServer(TransferDataServer &) = delete;
		TransferDataServer& operator=(TransferDataServer &) = delete;
	public:
		TransferDataServer(network::socket_t &&s);
	private:
		void askFileList();
		std::map<nameSize_p::first_type, nameSize_p::second_type> getFileList();
		void selectFile(std::map<nameSize_p::first_type, nameSize_p::second_type> &mapfile);
		void sendSelectFile();
		void receiveFromClient();
		void saveToFile(std::ofstream &fout);
	public:
		void run();
	};
	
}

#endif // TRANSFERDATASERVER_HPP
