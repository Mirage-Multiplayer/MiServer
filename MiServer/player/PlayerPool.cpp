#include "player/PlayerPool.hpp"

mimp::internal::player::PlayerPool::PlayerPool(unsigned short max_players): m_Pool(max_players, nullptr) {
	this->m_MaxPlayers = max_players;
}

