#include <MiServer/netgame/NetGame.hpp>

mimp::CNetGame::CNetGame(uint16_t max_players, uint16_t max_vehicles)
{
    this->m_pPlayerPool = new internal::CPool<Player>(max_players);
    this->m_pVehiclePool = new internal::CPool<Vehicle>(max_vehicles);
}

mimp::internal::CPool<mimp::Player> *mimp::CNetGame::GetPlayerPool()
{
    return this->m_pPlayerPool;
}

mimp::internal::CPool<mimp::Vehicle> *mimp::CNetGame::GetVehiclePool()
{
    return this->m_pVehiclePool;
}