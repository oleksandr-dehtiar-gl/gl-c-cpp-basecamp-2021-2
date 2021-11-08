#include <iostream>
#include <filesystem>
#include <exception>
#include <sstream>
#include <algorithm>

#include "transferDataClient.hpp"
#include <header.hpp>

#define THREAD_QUEUE_ELEMENT 10

namespace transfer {
	
	TransferDataClient::TransferDataClient(network::socket_t &&s) 
		: mSocket(std::move(s)), mFileSizeList(getFileList(".")),
		  mSafeQueue(THREAD_QUEUE_ELEMENT),
		  mStopRedingFile(true)
	{ 
	}
	
	bool TransferDataClient::receiveAskFileServer() {
		AskFileHeader askFileHead;
		mSocket.read((char*)&askFileHead, sizeof(AskFileHeader));
		std::cout << "ask: " << (askFileHead.getType() == headerType::REQUEST_FILELIST ? "REQUEST_FILELIST" : "ERROR! ASK FILE PACKET NOT DEFINE!") << std::endl;
		return true;
	}
	
	void TransferDataClient::sendFileList() {
		std::string fileListStr;
		{
			std::ostringstream sout;
			// reserve for header uint64_t (8byte)
			for (int i = 0; i < sizeof(FileListHeader); ++i) {
				sout << '\0';
			}
			for (auto &fileInfo : mFileSizeList) {
				sout << std::get<0>(fileInfo) << "\n" << std::get<1>(fileInfo) << "\n";
			}
			sout << "\r";
			fileListStr.assign(sout.str());
		}
		// set header
		FileListHeader headFileList(mFileSizeList.size(), fileListStr.size());
		headFileList.hostToNet();
		memcpy((void*)fileListStr.c_str(), &headFileList, sizeof(FileListHeader));
		
		unsigned int sizeBuf = fileListStr.size();
		const char* beginptr = fileListStr.c_str();
		const char* currentptr = beginptr;
		
		mSocket.writen(fileListStr.c_str(), fileListStr.size());
	}
	
	nameSize_p TransferDataClient::getFileInfoFromServer() {
		const unsigned int sizeBuf = 1024;
		static char buffer[sizeBuf];
		
		// read select file from server
		/* !!!!!!!!! No time! Fixed later. Read data from server can be less than entire name string.
			We need read all data untill "\n\r" or length file in headers ...
		*/
		FileInfoHeader fileInfo;
		unsigned int read = mSocket.read(buffer, sizeBuf);
		memcpy(&fileInfo, buffer, sizeof(FileInfoHeader));
		fileInfo.netToHost();

		return std::make_pair(std::string(buffer + sizeof(FileInfoHeader), read - sizeof(FileInfoHeader) - strlen(endFileList)), fileInfo.sizeFile());
	}
	
	void TransferDataClient::readFromFile(std::ifstream &fin) {
		auto *filebuf = fin.rdbuf();
		unsigned int dataread = 0;
		std::shared_ptr<DataPacket> pack;
		bool packisread = true;
		do {
			if (packisread) {
				pack = std::make_shared<DataPacket>(DataPacket());
				dataread = pack->size = filebuf->sgetn(pack->data, SIZE_PACKE_BUF);
			}
			packisread = mSafeQueue.try_push(pack);
		}
		while(dataread != 0);
		
		mStopRedingFile.store(false);
	}
	
	void TransferDataClient::sendFileToServer() {
		while(1) {
			std::shared_ptr<DataPacket> pack = mSafeQueue.try_pop();
			if (!pack) {
				if (!mStopRedingFile)
					if (mSafeQueue.empty())
						break;
				continue;
			}
			mSocket.writen(pack->data, pack->size);
		}
		mSocket.shutdownWrite();
	}
	
	void TransferDataClient::run() {
		std::cout << "transfer data client has been running...\n";
		
		// Receive request from server for send to him file list
		receiveAskFileServer();
		
		// Send to server file list
		sendFileList();
		auto pairNameSizeFile = getFileInfoFromServer();
		std::cout << "Select file from server is: " << std::get<0>(pairNameSizeFile) 
				  << " [" << std::get<1>(pairNameSizeFile) << "]" << std::endl;
		
		// find if file exist
		auto iter = std::find_if(mFileSizeList.begin(), mFileSizeList.end(), 
			[&pairNameSizeFile](nameSize_p& p) { return std::get<0>(p) == std::get<0>(pairNameSizeFile); });
		if (iter == mFileSizeList.end()) {
			std::cout << "File dosn't exist! CLIENT CLOSE!\n";
			return;
		}
		
		// Open file for send
		std::ifstream fin(std::get<0>(pairNameSizeFile), std::ios::in | std::ios::binary);
		if (!fin.is_open()) {
			std::cout << "Can not open file: " << std::get<0>(pairNameSizeFile) << ". CLIENT CLOSE!"<< std::endl;
			return;
		}
		
		// Run thread for read file data
		Threadguard readFileData(std::thread(&TransferDataClient::readFromFile, this, std::ref(fin)));
		Threadguard sendToServer(std::thread(&TransferDataClient::sendFileToServer, this));


	}
	
}
