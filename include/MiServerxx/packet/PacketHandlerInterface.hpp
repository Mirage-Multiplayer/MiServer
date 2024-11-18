#pragma once
#include <functional>
#include <vector>
#include <map>
namespace mimp {
	namespace internal {
		namespace packet {
			class PacketHandlerInterface {
			public:
				PacketHandlerInterface() = default;
				virtual void addPacketHandler(const int uid, std::function<void(const int, Packet*)>) = 0;
				virtual bool hasPacketHandler(const int uid) = 0;
				virtual void HandlePacket(const int uid, Packet* packet) = 0;
			protected:
				std::map<int, std::vector<std::function<void(const int, Packet*)>>> m_Packets;
			};
		}
	}
}
