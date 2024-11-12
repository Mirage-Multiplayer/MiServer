#ifndef __MISERVER_RPC_HPP
#define __MISERVER_RPC_HPP
#include <MiRak/BitStream.h>
#include <MiRak/RakEncr.h>
#include <MiRak/RakServer.h>
#include <MiServerxx/types.h>
#include <functional>
#include <cstdint>
#include <vector>
#include <unordered_map>

#define REJECT_REASON_BAD_VERSION 1
#define REJECT_REASON_BAD_NICKNAME 2
#define REJECT_REASON_BAD_MOD 3
#define REJECT_REASON_BAD_PLAYERID 4

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			class IRPC {
			public:
				using fn = std::function<void(RPCParameters*)>;
				IRPC(const int UID);
				void addHandler(fn handler);
				bool hasHandler(void);
				inline int GetUID(void) {
					return this->m_UID;
				}
				void Call(RPCParameters* params);

			private:
				int m_UID;
				std::vector<fn> m_handlers;
			};

			class RPCReceiverInterface {
			public:
				RPCReceiverInterface() = default;
				virtual bool RegisterRPC(IRPC* rpc) = 0;
				virtual IRPC* GetRPCHandler(const int rpcid) = 0;
				virtual void UnregisterRPC(const int rpcid) = 0;
			protected:
				std::unordered_map<int, IRPC*> m_RPCs;
			};
			
			struct ORPC {
			public:
				ORPC(const int UID) {
					this->m_UID = UID;
				}
				inline const int GetUID(void) const {
					return m_UID;
				}
				virtual void Write(RakNet::BitStream*) = 0;
			private:
				int m_UID;
			};

			class RPCEmitterInterface {
			public:
				RPCEmitterInterface() = default;
				virtual void SendRPC(const int playerid, ORPC* rpc) = 0;
				virtual void BroadcastRPC(ORPC* rpc) = 0;
				virtual void BroadcastRPC(ORPC* rpc, const int playerid) = 0;
			};

			/*
			template<uint16_t rpcid>
			class ORPC {
			public:
				using fn = std::function<void(RPCParameters*)>;
				IRPC(const int UID);
				void addHandler(fn handler);
				bool hasHandler(void);
				void Call(RPCParameters* params);
				inline int GetUID(void) {
					return this->m_UID;
				}

			private:
				int m_UID;
				std::vector<fn> m_handlers;
			};
			*/
		}
	}
}

#endif
