#ifndef __MISERVER_NETGAME_HPP
#define __MISERVER_NETGAME_HPP
#include <MiServerxx/netgame/Pool.hpp>
#include <MiServerxx/netgame/Player.hpp>
#include <MiServerxx/netgame/Vehicle.hpp>
#include <MiServerxx/netgame/Dialog.hpp>

namespace mimp
{
    class CNetGame
    {
    public:
        CNetGame(uint16_t max_players, uint16_t max_vehicles);
        internal::CPool<CPlayer> *GetPlayerPool();
        internal::CPool<CVehicle> *GetVehiclePool();

    private:
        internal::CPool<CPlayer> *m_pPlayerPool;
        internal::CPool<CVehicle> *m_pVehiclePool;
        internal::CPool<CDialog>* m_pDialogPool;
    };
}
#endif