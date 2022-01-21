#pragma once


enum PacketType : uint32_t
{
	InvalidPacket,
	ProcessListRequestPacket,
	ProcessToTerminateRequestPacket,
	ProcessListResponsePacket,
	ProcessTerminatedResponsePacket
};
