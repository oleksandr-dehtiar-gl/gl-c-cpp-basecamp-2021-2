#pragma once


enum PacketType : uint32_t
{
	InvalidPacket,
	ProcessListRequestPacket,
	ProcessPairRequestPacket,
	ProcessListResponsePacket,
	ProcessTerminatedResponsePacket
};