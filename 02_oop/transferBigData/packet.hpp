#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstring>
#include <vector>

#include <cstdint>
#include <netApi.hpp>

const unsigned short PACKET_SIZE = 4096;

const char BUFFER_PLACEHOLDER = '\0';
const char * const END_TEXT_DATA = "\n\r";

namespace transferApp {

	class Packet {
	public:
		enum : uint8_t {
			NOT_TYPE = 0,
			REQUEST_FILES,
			SEND_FILE_LIST,
			SEND_SELECT_FILE,
			SEND_FILE
		};
		struct packetHeader_t {
			union {
				struct {
					struct {
						uint8_t typePacket;
						uint8_t fileNameLength;
					};
					union {
						uint16_t  countFile;
						uint16_t  availSpaceBuf;
					};
					uint32_t fileSize;
				};
				uint64_t packet64_t;
			};
		};
		union packet_t {
			packetHeader_t head;
			unsigned char data[PACKET_SIZE];
		};
	private:
		packet_t mPacket;
	public:
		Packet() { 
			memset(&mPacket, BUFFER_PLACEHOLDER, sizeof(mPacket)); 
			resetPacketData();
			setType(NOT_TYPE);
		}
	public:
		uint8_t  getType() { return mPacket.head.typePacket; }
		void setType(uint8_t type) { mPacket.head.typePacket = type; }
				 
		uint16_t getCountFile() { return mPacket.head.countFile; }
		void setCountFile(uint16_t n) { mPacket.head.countFile = n; }
				 
		uint32_t getFileSize() { return mPacket.head.fileSize; }
		void setFileSize(uint32_t sizeFile) { mPacket.head.fileSize = sizeFile; }
				 
		uint16_t getFileNameLength() { return mPacket.head.fileNameLength; }
		void setFileNameLength(uint16_t length) { mPacket.head.fileNameLength = length; }
		
		void htonHeader() { mPacket.head.packet64_t = network::hostToNet_u64(mPacket.head.packet64_t); }
		void ntohHeader() { mPacket.head.packet64_t = network::netToHost_u64(mPacket.head.packet64_t); }
	private:
		char* ptrData() { return (char*)(&mPacket) + sizeHeader(); }
		char* ptrPacket() { return (char*)(&mPacket); }
	public:
		static inline unsigned int sizePacket() { return sizeof(packet_t); }
		static inline unsigned int sizeHeader() { return sizeof(packetHeader_t); }
		static inline unsigned int sizeData() { return sizePacket() - sizeHeader(); }
	public:
		bool typeIsEqual(uint8_t typePacket) { return typePacket == mPacket.head.typePacket ? true : false; }
		
		void resetPacketData() { mPacket.head.availSpaceBuf = sizeData(); }
		unsigned short availToAdd() { return mPacket.head.availSpaceBuf; }
		
		uint32_t getPacketDataSize() { return sizeData() - mPacket.head.availSpaceBuf; }
		uint32_t getPacketSize() { return getPacketDataSize() + sizeHeader(); }
		
		unsigned short addDataToPacket(const char* data, unsigned int n) {
			if (n > mPacket.head.availSpaceBuf)
				return 0;
			char *posToWrite = ptrData() + (sizeData() - mPacket.head.availSpaceBuf);
			memcpy(posToWrite, data, n);
			mPacket.head.availSpaceBuf -= n;
			return n;
		}
	public:
		packetHeader_t getHeader() { return mPacket.head; }
		void setHeader(packetHeader_t head) { mPacket.head = head; }
		std::string getDataStr(unsigned int n) { return n > sizeData() ? std::string() : std::move(std::string(ptrData(), n)); }
	};

}

#endif // PACKET_HPP
