#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <iostream>

#include <network.hpp>

namespace transfer {
	
	// end of filelist string
	static const char* endFileList = "\n\r";
	
	enum headerType : uint8_t {
		REQUEST_FILELIST = 1,
		ANSWER_FILELIST,
		SELECT_FILE,
		DATA
	};
	
	class AskFileHeader {
	private:
		headerType type;
	public:
		AskFileHeader() : type(headerType::REQUEST_FILELIST) {}
		headerType getType() const { return type; }
	};
	
	class FileListHeader { 
	private:
		union {
			uint64_t head64_t;
			struct {
				headerType type;
				uint8_t : 8; // placeholder for elignment
				uint16_t numFiles;
				uint32_t sizePacket;
			};
		} mHeader;
	public:
		FileListHeader() {
			mHeader.type = headerType::ANSWER_FILELIST;
			mHeader.numFiles = 0;
			mHeader.sizePacket = 0;
		}
		
		FileListHeader(uint32_t totalFiles, uint16_t entireStringSize) {
			mHeader.type = headerType::ANSWER_FILELIST;
			mHeader.numFiles = totalFiles;
			mHeader.sizePacket = entireStringSize;
		}
	public:
		headerType type() const { return mHeader.type; }
		uint16_t countFiles() const { return mHeader.numFiles; }
		uint32_t sizePacket() const { return mHeader.sizePacket; }
	public:
		void hostToNet() { mHeader.head64_t = network::hostToNet_u64(mHeader.head64_t); }
		void netToHost() { mHeader.head64_t = network::netToHost_u64(mHeader.head64_t); }
		friend std::ostream& operator<<(std::ostream &out, FileListHeader& header);
	};
	
	class FileInfoHeader {
	private:
		union {
			uint64_t head64_t;
			struct {
				uint64_t type : 8;
				uint64_t nameLength : 16;
				uint64_t fileSize : 40;
			};
		} mHeader;
	public:
		FileInfoHeader() {
			memset(this, 0, sizeof(FileInfoHeader));
			mHeader.type = headerType::SELECT_FILE;
		}
		FileInfoHeader(uint16_t length, uint64_t size) {
			memset(this, 0, sizeof(FileInfoHeader));
			mHeader.type = headerType::SELECT_FILE;
			mHeader.nameLength = length;
			mHeader.fileSize = size;
		}
	public:
		headerType type() const { return (headerType)mHeader.type; }
		uint16_t lengthFileName() const { return mHeader.nameLength; }
		uint64_t sizeFile() const { return mHeader.fileSize; }
		
		void hostToNet() { mHeader.head64_t = network::hostToNet_u64(mHeader.head64_t); }
		void netToHost() { mHeader.head64_t = network::netToHost_u64(mHeader.head64_t); }
		
		friend std::ostream& operator<<(std::ostream &out, FileInfoHeader& header);
	};
	
	
}
	
#endif // HEADERS_HPP
