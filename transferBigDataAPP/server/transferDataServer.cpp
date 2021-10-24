#include <iostream>
#include <list>

#include <netApi.hpp>
#include <threadGuard.hpp>
#include <transferUtility.hpp>

#include "transferDataServer.hpp"

#define THREAD_QUEUE_ELEMENT 10

namespace transferApp {
	
	TtransferDataServer::TtransferDataServer(const char *hostname, const char *servname)
	: mConnection(network::tcpConnect(hostname, servname)),
	  mSafeQueue(THREAD_QUEUE_ELEMENT),
	  mStopReadSock(true)
	{
		init(std::string("TtransferDataServer(const char *hostname, const char *servname)") + " host: " + hostname + " serv: " + servname);
	}
	
	TtransferDataServer::TtransferDataServer(SocketConnection &&connection)
	: mConnection(std::move(connection)),
	  mSafeQueue(THREAD_QUEUE_ELEMENT),
	  mStopReadSock(true)
	{	
		init(std::string("TtransferDataServer(SocketConnection &&)"));
	}
	
	void TtransferDataServer::init(std::string ermsg) {
		if (!mConnection.connectIsValid()) {
			network::printErrorMessage(network::getLastSocketError());
			throw ExceptionTtransferDataServer(ermsg);
		}
	}
	
	void TtransferDataServer::processData() {
		while(1) {
			std::shared_ptr<PackFile> pack = mSafeQueue.try_pop();
			if (!pack) {
				if (!mStopReadSock)
					if (mSafeQueue.empty())
						break;
				continue;
			}
			mFoutbuf->sputn(pack->buf, pack->size);
		}
	}

	void TtransferDataServer::send() {
		
	}
	
	void TtransferDataServer::receive() {
		unsigned int dataread = 0;
		std::shared_ptr<PackFile> pack;
		bool packisread = true;
		do {
			if (packisread) {
				pack = std::make_shared<PackFile>(PackFile());
				dataread = pack->size = mConnection.readn(pack->buf, SIZE_PACKE_BUF);
			}
			packisread = mSafeQueue.try_push(pack);
		}
		while(dataread != 0);
		
		mStopReadSock = false;
	}
	
	std::string TtransferDataServer::showAndSelectFile() {
		std::shared_ptr<Packet> pack(new Packet);
		
		unsigned int datasize = Packet::sizePacket();
		unsigned int dataread = Packet::sizePacket();
		std::string packmsg;
		std::list<std::string> fileList;
		while((datasize = mConnection.read((char*)(&*pack), datasize)) == dataread) {
			std::swap(pack->getDataStr(datasize), packmsg);
			fileList.push_back(std::move(packmsg));
		}
		std::swap(pack->getDataStr(datasize), packmsg);
		fileList.push_back(std::move(packmsg));
		
		std::cout << "List of file from client:\n";
		for (auto &str : fileList) {
			std::cout << str;
		}
		
		std::cout << "\nSelect a file from the list and write it below: \nFile name: ";
		std::getline(std::cin, packmsg);
		
		return std::move(packmsg);
	}
	
	void TtransferDataServer::run() {
		
		// Send request for send file list
		std::shared_ptr<Packet> pack(new Packet);
		pack->setType(Packet::REQUEST_FILES);
		
		unsigned int datasize = pack->getPacketSize();
		pack->htonHeader();
		datasize = mConnection.writen((char*)(&*pack), datasize);
		
		// Receive file list
		std::string selectFile(std::move(showAndSelectFile()));
		
		// Request for send slect file file
		pack->resetPacketData();
		pack->setType(Packet::SEND_SELECT_FILE);
		pack->setFileNameLength(selectFile.length());
		pack->addDataToPacket(selectFile.c_str(), selectFile.length());
		mConnection.writen((char*)(&*pack), pack->getPacketSize());
		
		// START RECEIVE FILE
		// Open file
		mFout.open(selectFile, std::ios::out | std::ios::binary);
		if (!mFout.is_open()) {
			std::cerr << "Erro open file\n";
			return;
		}
		mFoutbuf = mFout.rdbuf();
		Threadguard processData(std::thread(&TtransferDataServer::processData, this));
		Threadguard receive(std::thread(&TtransferDataServer::receive, this));
		
		
		// PAUSE FOR TEST
		// std::cout << "Press enter to continue...\n";
		// std::cin.get();
	}

}
