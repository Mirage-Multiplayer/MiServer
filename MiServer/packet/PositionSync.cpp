#include <MiServer/packet/PositionSync.hpp>
#include <MiServer/packet/PassengerSync.hpp>
#include <MiServer/player/PlayerTypes.hpp>
#include <MiServer/player/PlayerPool.hpp>
#include <MiServer/player/Player.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/server/Server.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>

void mimp::internal::packet::UpdatePosition(int iPlayerID, float fX, float fY, float fZ)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	mimp::internal::player::PlayerPool *pPlayerPool = mimp::internal::server::GetServerInstance()->getPlayerPool();

	mimp::Player *pPlayer = pPlayerPool->Get(iPlayerID);

	if (pPlayer->m_checkpointActive)
	{
		float fSX = (fX - pPlayer->m_checkpointPos[0]) * (fX - pPlayer->m_checkpointPos[0]);
		float fSY = (fY - pPlayer->m_checkpointPos[1]) * (fY - pPlayer->m_checkpointPos[1]);
		float fSZ = (fZ - pPlayer->m_checkpointPos[2]) * (fZ - pPlayer->m_checkpointPos[2]);

		if ((float)sqrt(fSX + fSY + fSZ) < pPlayer->m_checkpointSize)
		{
			if (!pPlayer->m_playerInCheckpoint)
			{
				pPlayer->m_playerInCheckpoint = true;

				// OnPlayerEnterCheckpoint
			}
		}
		else
		{
			if (pPlayer->m_playerInCheckpoint)
			{
				pPlayer->m_playerInCheckpoint = false;

				// OnPlayerExitCheckpoint
			}
		}
	}
	mimp::internal::event::OnPlayerUpdate_params params;
	params.player = pPlayer;
	mimp::internal::server::GetServerInstance()->getEventPool()->Emit(mimp::internal::event::SERVER_EVENT_PLAYERUPDATE, static_cast<void *>(&params));
}