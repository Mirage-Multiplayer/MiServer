#pragma once
#include <unordered_map>
#include <MiServerxx/RPC/RPC.hpp>
namespace mimp
{
	namespace internal
	{
		namespace RPC {
			class RPCReceiver {
			public:
				using fn = std::function<void(RPCParameters* params)>;
				RPCReceiver(bool useDefault);
				void OnRPC(const int rpcid, fn handler);
				const bool hasHandler(const int rpcid);
				const bool hasRPC(const int rpcid);
				std::vector<fn> GetHandlers(const int rpcid);
			private:
				std::unordered_map<int, std::vector<fn>> m_RPCMap;
			};
		}
	}
}
