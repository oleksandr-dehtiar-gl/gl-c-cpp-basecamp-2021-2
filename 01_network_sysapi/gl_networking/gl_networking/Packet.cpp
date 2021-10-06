#include "Packet.h"

void Packet::Clear()
{
	m_bytes.clear();
	m_extractionOffset = 0;
}

void Packet::Append(const void * data, size_t numberOfBytes)
{
	m_bytes.insert(m_bytes.end(), (char*)data, (char*)data + numberOfBytes);
}

Packet & Packet::operator << (uint32_t data)
{
	data = htonl(data);
	Append(&data, sizeof(data));
	return *this;
}

Packet & Packet::operator >> (uint32_t & data)
{
	data = *reinterpret_cast<uint32_t*>(m_bytes.data() + m_extractionOffset);
	data = ntohl(data);
	m_extractionOffset += sizeof(data);
	return *this;

}
