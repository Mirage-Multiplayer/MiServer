#include <MiServerxx/netgame/NetGame.hpp>

mimp::CNetGame::CNetGame(uint16_t max_players, uint16_t max_vehicles)
{
    this->m_pPlayerPool = new internal::CPool<CPlayer>(max_players);
    this->m_pVehiclePool = new internal::CPool<CVehicle>(max_vehicles);
}

mimp::internal::CPool<mimp::CPlayer> *mimp::CNetGame::GetPlayerPool()
{
    return this->m_pPlayerPool;
}

mimp::internal::CPool<mimp::CVehicle> *mimp::CNetGame::GetVehiclePool()
{
    return this->m_pVehiclePool;
}