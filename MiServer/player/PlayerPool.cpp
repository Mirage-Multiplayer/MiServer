#include "player/PlayerPool.hpp"

mimp::internal::player::PlayerPool::PlayerPool(unsigned short max_players): m_Pool(max_players, nullptr) {
	this->m_MaxPlayers = max_players;
}

int mimp::internal::player::PlayerPool::Add(Player* p) {
	const PLAYERID id = p->getPlayerId();
	if (this->m_Pool.at(id) != nullptr) {
		this->Remove(id);
	}

	auto it = this->m_Pool.begin() + id;
	this->m_Pool.insert(it, p);
	return -1;
}

int mimp::internal::player::PlayerPool::Remove(const PLAYERID id) {
	if (id < 0 || id >= this->m_MaxPlayers || this->m_Pool.at(id) == nullptr) {
		return -1;
	}

	delete this->m_Pool[id];
	this->m_Pool[id] = nullptr;
	return 1;
}

mimp::Player* mimp::internal::player::PlayerPool::Get(const PLAYERID id) {
	if (id < 0 || id >= this->m_MaxPlayers) {
		return nullptr;
	}

	return this->m_Pool.at(id);
}

const bool mimp::internal::player::PlayerPool::IsPlayerConnected(const PLAYERID id) const {
	if (id < 0 || id >= this->m_MaxPlayers) {
		return false;
	}

	if (this->m_Pool.at(id) == nullptr) {
		return false;
	}

	return true;
}