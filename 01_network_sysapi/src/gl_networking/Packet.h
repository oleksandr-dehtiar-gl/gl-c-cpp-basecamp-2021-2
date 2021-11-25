#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock.h>
#else 
#include <cstdint>
#include <arpa/inet.h>
#endif
#include "PacketType.h"
#include <vector>
#include <string>

class Packet
{
public:

	Packet(PacketType packetType = PacketType::InvalidPacket);
	void Clear();
	void Append(const void * data, size_t numberOfBytes);
	inline size_t GetPacketSize() { return m_bytes.size(); };
	inline void * GetPacketData() { return m_bytes.data(); };
	inline void Resize(size_t size) { m_bytes.resize(size); };
	Packet & operator << (const uint32_t & data);
	Packet & operator >> (uint32_t & data);
	Packet & operator << (const std::string & str);
	Packet & operator >> (std::string & str);
	PacketType GetPacketType();
	void AssignPacketType(PacketType packetType);



private:
	std::vector<char> m_bytes;
	uint32_t m_extractionOffset = 0;


};


