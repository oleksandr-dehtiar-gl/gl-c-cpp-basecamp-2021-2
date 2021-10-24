#include <iostream>
#include <cstring>

#include <netApi.hpp>
#include <threadGuard.hpp>
#include <transferUtility.hpp>

#include "transferDataClient.hpp"

#define THREAD_QUEUE_ELEMENT 10

namespace transferApp {
	
	TtransferDataClient::TtransferDataClient(const char *hostname, const char *servname)
	: mConnection(network::tcpConnect(hostname, servname)),
	  mSafeQueue(THREAD_QUEUE_ELEMENT),
	  mStopRedingFile(true)
	{
		init(std::string("TtransferDataClient(const char *hostname, const char *servname)") + " host: " + hostname + " serv: " + servname);
	}
	
	TtransferDataClient::TtransferDataClient(SocketConnection &&connection)
	: mConnection(std::move(connection)),
	  mSafeQueue(THREAD_QUEUE_ELEMENT),
	  mStopRedingFile(true)
	{	
		init(std::string("TtransferDataClient(SocketConnection &&)"));
	}
	
	void TtransferDataClient::init(std::string ermsg) {
		if (!mConnection.connectIsValid()) {
			network::printErrorMessage(network::getLastSocketError());
			throw ExceptionTtransferDataClient(ermsg);
		}
		std::swap(transferApp::getFilesFromDir(std::string(".")), mFileList);
		if (mFileList.empty()) {
			throw ExceptionTtransferDataClient(std::string("ERROR! NO FILES TO SEND!"));
		}
	}
	
	void TtransferDataClient::prepareData() {
		unsigned int dataread = 0;
		std::shared_ptr<PackFile> pack;
		bool packisread = true;
		do {
			if (packisread) {
				pack = std::make_shared<PackFile>(PackFile());
				dataread = pack->size = mFinbuf->sgetn(pack->buf, SIZE_PACKE_BUF);
			}
			packisread = mSafeQueue.try_push(pack);
		}
		while(dataread != 0);
		
		mStopRedingFile = false;
	}

	void TtransferDataClient::send() {
		while(1) {
			std::shared_ptr<PackFile> pack = mSafeQueue.try_pop();
			if (!pack) {
				if (!mStopRedingFile)
					if (mSafeQueue.empty())
						break;
				continue;
			}
			mConnection.writen(pack->buf, pack->size);
		}
		mConnection.shutdownWrite();
	}
	
	void TtransferDataClient::receive() {

	}
	
	void TtransferDataClient::sendFileList() {
		std::shared_ptr<Packet> pack(new Packet);
		pack->setType(Packet::SEND_FILE_LIST);
		pack->setCountFile(mFileList.size());
		pack->htonHeader();
		
		pack->resetPacketData();
		unsigned int countFiles = mFileList.size();	
		unsigned int sveDataInPack = 0;
		
		std::string prefixFile(" - ");
		std::string endlineFile("\n");
		std::string endingFile(END_TEXT_DATA);
		
		for (auto iter = mFileList.begin(); ; ++iter) {
			--countFiles;
			unsigned short nameLength = (unsigned short)std::get<0>(*iter).length();
			unsigned int addStatus = pack->addDataToPacket((prefixFile + std::get<0>(*iter) + endlineFile).c_str(), 
									nameLength + prefixFile.length() + endlineFile.length());
			if (countFiles == 0) {
				char endTextSymbol = '\r';
				if (addStatus && pack->availToAdd()) {
					pack->addDataToPacket(&endTextSymbol, 1);
					mConnection.writen((char*)(&*pack), pack->getPacketSize());
				} else {
						mConnection.writen((char*)(&*pack), pack->getPacketSize());
						pack->resetPacketData();
					if (addStatus) {
						pack->addDataToPacket(&endTextSymbol, 1);
						mConnection.writen((char*)(&*pack), pack->getPacketSize());
					} else {
						pack->addDataToPacket((prefixFile + std::get<0>(*iter) + endingFile).c_str(), 
											nameLength + prefixFile.length() + endingFile.length());
						mConnection.writen((char*)(&*pack), pack->getPacketSize());
					}
				}
				break;
			} else {
				if (!addStatus) {
					mConnection.writen((char*)(&*pack), pack->getPacketSize());
					pack->resetPacketData();
					pack->addDataToPacket((prefixFile + std::get<0>(*iter) + endlineFile).c_str(), 
									nameLength + prefixFile.length() + endlineFile.length());
				}
			}
		}
	}
	
	void TtransferDataClient::run() {
		// Recive request for send file list
		std::shared_ptr<Packet> pack(new Packet);
		
		unsigned int datalength =  mConnection.read((char*)(&*pack), pack->sizePacket());
		pack->ntohHeader();
		if (!pack->typeIsEqual(Packet::REQUEST_FILES)) {
			std::cerr << "FATAL ERROR! UNDEFINE PACKET TYPE!\n";
			return;
		}
	
		// Send list of file
		sendFileList();
		
		// Recive select file name from server
		pack->resetPacketData();
		datalength = mConnection.read((char*)(&*pack), Packet::sizePacket());
		std::string selectFile(std::move(pack->getDataStr(datalength - Packet::sizeHeader())));
		std::cout << "Select file: " << selectFile << std::endl;
		
		pack->resetPacketData();
		pack->setType(Packet::SEND_FILE);
		uint32_t fileSize = 0;
		for (auto &file : mFileList ) {
			if (std::get<0>(file) == selectFile) {
				pack->setFileSize(std::get<1>(file));
				std::cout << "File exist: " << std::get<0>(file) << " [" << std::get<1>(file) << "]" << std::endl;
				break;
			}
		}
		
		// SEND FILE
		std::cout << "Start send file: " << selectFile << " ...\n";
		
		// Open file
		mFin.open(selectFile, std::ios::in | std::ios::binary);
		if (!mFin.is_open()) {
			std::cerr << "Erro open file\n";
			return;
		}
		mFinbuf = mFin.rdbuf();

		
		// This is not what I wanted to do, but my time is running out and therefore I want to get some working version ...
		Threadguard prepareTread(std::thread(&TtransferDataClient::prepareData, this));
		Threadguard sendTread(std::thread(&TtransferDataClient::send, this));

	}

}
