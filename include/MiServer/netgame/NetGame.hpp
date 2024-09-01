#ifndef __MISERVER_NETGAME_HPP
#define __MISERVER_NETGAME_HPP
#include <MiServer/netgame/Pool.hpp>
#include <MiServer/netgame/Player.hpp>
#include <MiServer/netgame/Vehicle.hpp>

namespace mimp
{
    class CNetGame
    {
    public:
        CNetGame(uint16_t max_players, uint16_t max_vehicles);
        internal::CPool<Player> *GetPlayerPool();
        internal::CPool<Vehicle> *GetVehiclePool();

    private:
        internal::CPool<Player> *m_pPlayerPool;
        internal::CPool<Vehicle> *m_pVehiclePool;
    };
}
#endif