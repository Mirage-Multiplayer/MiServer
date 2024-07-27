#ifndef __MISERVER_PLAYERPOOL_HPP
#define __MISERVER_PLAYERPOOL_HPP
#include <vector>
#include "Player.hpp"
namespace mimp {
	namespace internal {
		namespace player {
			class PlayerPool {
			public:
				PlayerPool() = default;
				PlayerPool(unsigned short max_players);
				inline int Add(Player* p) {
					for (int i = 0; i < this->m_MaxPlayers; i++) {
						if (this->m_Pool.at(i) == nullptr) {
							this->m_Pool[i] = p;
							return i;
						}
					}
					return -1;
				}

				inline int Remove(const PLAYERID id) {
					if (id < 0 || id >= this->m_MaxPlayers || this->m_Pool[id] == nullptr) {
						return -1;
					}
					delete this->m_Pool[id];
					this->m_Pool[id] = nullptr;
					return 1;
				}

				inline Player* Get(const PLAYERID id) {
					if (id < 0 || id >= this->m_MaxPlayers) {
						return nullptr;
					}

					return this->m_Pool.at(id);
				}
			private:
				unsigned short m_MaxPlayers;
				std::vector<Player*> m_Pool;
			};
		}
	}
}
#endif