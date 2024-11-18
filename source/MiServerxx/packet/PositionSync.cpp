#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::packet;
void UpdatePosition(WORD iPlayerID, float fX, float fY, float fZ) {
	RakServerInterface* pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(iPlayerID);

	if (pPlayer->getCheckpointActive())
	{
		float posx, posy, posz;
		pPlayer->getCheckpointPos(posx, posy, posz);
		float fSX = (fX - posx) * (fX - posx);
		float fSY = (fY - posy) * (fY - posy);
		float fSZ = (fZ - posz) * (fZ - posz);

		if ((float)sqrt(fSX + fSY + fSZ) < pPlayer->getCheckpointSize())
		{
			if (!pPlayer->isPlayerInCheckpoint())
			{
				pPlayer->_setPlayerInCheckpoint(true);

				// OnPlayerEnterCheckpoint
			}
		}
		else
		{
			if (pPlayer->isPlayerInCheckpoint())
			{
				pPlayer->_setPlayerInCheckpoint(false);

				// OnPlayerExitCheckpoint
			}
		}
	}
	MIMP_GET_EVENT(PLAYERUPDATE, mimp::internal::server::GetCoreInstance()->getEventPool())
		PLAYERUPDATE->Emit(pPlayer);
}