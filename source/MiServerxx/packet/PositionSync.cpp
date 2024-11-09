#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>

void mimp::internal::packet::UpdatePosition(int iPlayerID, float fX, float fY, float fZ)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer> *pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	mimp::CPlayer *pPlayer = pPlayerPool->GetAt(iPlayerID);

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
	MIMP_GET_EVENT(PLAYERUPDATE, mimp::internal::server::GetCoreInstance()->getEventPool())
		PLAYERUPDATE->Emit(pPlayer);
}