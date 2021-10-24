#include "Packet.h"

Packet::Packet(PacketType packetType)
{
	Clear();
	AssignPacketType(packetType);
}

void Packet::Clear()
{
	m_bytes.resize(sizeof(PacketType));
	AssignPacketType(PacketType::InvalidPacket);
	m_extractionOffset = sizeof(PacketType);
}

void Packet::Append(const void * data, size_t numberOfBytes)
{
	m_bytes.insert(m_bytes.end(), (char*)data, (char*)data + numberOfBytes);
}

Packet & Packet::operator << (const uint32_t & data)
{
	uint32_t encodedData = htonl(data);
	Append(&encodedData, sizeof(uint32_t));
	return *this;
}

Packet & Packet::operator >> (uint32_t & data)
{
	if ((m_extractionOffset + sizeof(uint32_t)) > m_bytes.size())
	{
		throw std::exception();
	}
	data = *reinterpret_cast<uint32_t*>(m_bytes.data() + m_extractionOffset);
	data = ntohl(data);
	m_extractionOffset += sizeof(data);
	return *this;

}

Packet & Packet::operator<<(const std::string & str)
{

	*this <<(uint32_t) str.size();
	Append(str.data(), str.size());
	return *this;
}

Packet & Packet::operator >> (std::string & str)
{

	
	str.clear();
	size_t strSize = 0;
	*this >> (uint32_t&)strSize;
	str.resize(strSize);
	if ((m_extractionOffset + strSize) > m_bytes.size())
	{
		throw std::exception();
	}

	str.assign(m_bytes.data() + m_extractionOffset, strSize);
	m_extractionOffset += strSize;


	return *this;
}

PacketType Packet::GetPacketType()
{
	PacketType * ptrPacketType = reinterpret_cast<PacketType*> (m_bytes.data());
	return static_cast<PacketType>(ntohl(ptrPacketType[0]));
}

void Packet::AssignPacketType(PacketType packetType)
{
	PacketType * ptrPacketType = reinterpret_cast<PacketType*> (m_bytes.data());
	ptrPacketType[0] = static_cast<PacketType>(htonl(packetType));
}
