#include "RPCList.hpp"


#define REJECT_REASON_BAD_VERSION	1
#define REJECT_REASON_BAD_NICKNAME	2
#define REJECT_REASON_BAD_MOD		3
#define REJECT_REASON_BAD_PLAYERID	4

namespace mimp {
	namespace internal {
		namespace RPC {
			void RegisterServerRPCs(RakServerInterface* pRakServer);
			void UnRegisterServerRPCs(RakServerInterface* pRakServer);
		}
	}
}
