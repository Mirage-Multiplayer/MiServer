#include "player/Player.hpp"

mimp::internal::player::Player::Player(PlayerID rakPlayerID, PLAYERID playerID, const char* nickname) {
	this->m_rakPlayerId = rakPlayerID;
	this->m_playerId = playerID;
	this->m_nickName = std::string(nickname);
}

