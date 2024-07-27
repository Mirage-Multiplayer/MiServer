#ifndef __MISERVER_PLAYER_HPP
#define __MISERVER_PLAYER_HPP
#include <string>
#include <MiRak/NetworkTypes.h>
#include "PlayerTypes.hpp"

namespace mimp {
	namespace internal {
		namespace player {
			class Player {
			public:
				Player(PlayerID rakPlayerID, PLAYERID playerID, const char* nickname);
			private:
				PLAYERID m_playerId;
				PlayerID m_rakPlayerId;
				std::string m_nickName;
			};
		}
	}
}
#endif