#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <sstream>

#include "transferDataServer.hpp"

#define THREAD_QUEUE_ELEMENT 10

namespace transfer {
	
	TransferDataServer::TransferDataServer(network::socket_t &&s) 
	: mSocket(std::move(s)),
	  mSafeQueue(THREAD_QUEUE_ELEMENT),
	  mStopReadSock(true)
	{ }
	
	void TransferDataServer::askFileList() {
		AskFileHeader askFileHead;
		mSocket.write((char*)&askFileHead, sizeof(AskFileHeader));
	}
	
	std::map<nameSize_p::first_type, nameSize_p::second_type> TransferDataServer::getFileList() {
		const int sizeBuf = 1024;
		static char buf[sizeBuf];
		
		// read first block data 
		int readnum = sizeBuf;
		std::string namefiles;
		readnum = mSocket.read(buf, sizeBuf);
		
		// Fill header structure
		FileListHeader headFileList;
		memcpy(&headFileList, buf, sizeof(FileListHeader));
		headFileList.netToHost();
		
		// read all files if exist
		namefiles.assign(buf + sizeof(FileListHeader), readnum - sizeof(FileListHeader));
		int lefttoread = headFileList.sizePacket();
		do {
			lefttoread -= readnum;
			if ((!strncmp((buf + readnum - strlen(endFileList)), endFileList, strlen(endFileList))) || (lefttoread <= 0)) {
				break;
			}
			readnum = mSocket.read(buf, sizeBuf);
			namefiles += std::string(buf, readnum);
		}
		while(1);

		// parse files and separate it by name and length and save to map
		std::map<nameSize_p::first_type, nameSize_p::second_type> fileList;
		auto begin = namefiles.begin();
		auto end = begin;
		nameSize_p pNameLength;
		
		std::cout << "File list:\n";
		int fileNumber = 0;
		while(end != namefiles.end()) {
			// find file name
			end = std::find_if(begin, namefiles.end(), [](char c) { return c == '\n'; } );
			if (end == namefiles.end()) 
				break;
			std::string(begin, end).swap(std::get<0>(pNameLength));
			begin = ++end;
			
			// find file length
			end = std::find_if(begin, namefiles.end(), [](char c) { return c == '\n'; } );
			if (end == namefiles.end()) 
				break;
			std::get<1>(pNameLength) = std::stoul(std::string(begin, end));
			
			// show file information whith number
			std::cout << fileNumber++ << ". " << std::get<0>(pNameLength) << " [" << std::get<1>(pNameLength) << "]\n";
			fileList.insert(std::move(pNameLength));
			begin = ++end;
		}
		std::cout << "Select file name and write it below ... \n";
		return std::move(fileList);
	}
	
	void TransferDataServer::selectFile(std::map<nameSize_p::first_type, nameSize_p::second_type> &mapfile) {
		int i = 4;
		do {
			std::getline(std::cin, std::get<0>(mFileInfo));
			auto element = mapfile.find(std::get<0>(mFileInfo));
			if (element == mapfile.end()) {
				std::cout << "File doesn't exist! You have " << i - 1
						<< " attempts left! Please write file name correctly!\n";
				continue;
			}
			std::get<1>(mFileInfo) = element->second;
			break;
		} while (--i > 0);
		
		if (i == 0)
			throw std::invalid_argument("No select file for rececive!");
		
		std::cout << "You select file: "
				  << std::get<0>(mFileInfo) << " [" << std::get<1>(mFileInfo) << "]" << std::endl;
	}
	
	void TransferDataServer::sendSelectFile() {
		// fill buffer whith space for header, name file string and size file in string format
		std::ostringstream fileInfoData;
		fileInfoData << std::string(sizeof(FileInfoHeader), '\0') << std::get<0>(mFileInfo) << endFileList;
		
		// set header
		FileInfoHeader header(std::get<0>(mFileInfo).length(), std::get<1>(mFileInfo));
		header.hostToNet();
		std::string fileInfo(fileInfoData.str());
		memcpy((void*)fileInfo.c_str(), &header, sizeof(FileInfoHeader));
		
		// send packet to client
		mSocket.writen(fileInfo.c_str(), fileInfo.length());
	}
	
	void TransferDataServer::receiveFromClient() {
		unsigned int dataread = 0;
		std::shared_ptr<DataPacket> pack;
		bool packisread = true;
		do {
			if (packisread) {
				pack = std::make_shared<DataPacket>(DataPacket());
				dataread = pack->size = mSocket.readn(pack->data, SIZE_PACKE_BUF);
			}
			packisread = mSafeQueue.try_push(pack);
		}
		while(dataread != 0);
		
		mStopReadSock.store(false);
	}
	
	void TransferDataServer::saveToFile(std::ofstream &fout) {
		auto *filebuf = fout.rdbuf();
		while(1) {
			std::shared_ptr<DataPacket> pack = mSafeQueue.try_pop();
			if (!pack) {
				if (!mStopReadSock)
					if (mSafeQueue.empty())
						break;
				continue;
			}
			filebuf->sputn(pack->data, pack->size);
		}
	}
	
	void TransferDataServer::run() {
		std::cout << "transfer data server has been running...\n";
		
		askFileList();
		
		auto files(getFileList());

		selectFile(files);
		
		// Open file for save
		std::ofstream fout(std::get<0>(mFileInfo), std::ios::out | std::ios::binary);
		if (!fout.is_open()) {
			std::cout << "Can not open file: " << std::get<1>(mFileInfo) << ". End connection whith clent!\n";
			return;
		}
		
		// Send file that we are select
		sendSelectFile();
		
		// Run thread for receive file data from client
		Threadguard receiveFromClient(std::thread(&TransferDataServer::receiveFromClient, this));
		Threadguard saveToFile(std::thread(&TransferDataServer::saveToFile, this, std::ref(fout)));
		
	}

}
