#ifndef __MISERVER_PLAYERPOOL_HPP
#define __MISERVER_PLAYERPOOL_HPP
#include <vector>
#include <MiServer/player/Player.hpp>
namespace mimp
{
	namespace internal
	{
		namespace player
		{
			class PlayerPool
			{
			public:
				PlayerPool() = default;
				PlayerPool(unsigned short max_players);
				int Add(Player *p);

				int Remove(const PLAYERID id);

				Player *Get(const PLAYERID id);

				const bool IsPlayerConnected(const PLAYERID id) const;

			private:
				unsigned short m_MaxPlayers;
				std::vector<Player *> m_Pool;
			};
		}
	}
}
#endif