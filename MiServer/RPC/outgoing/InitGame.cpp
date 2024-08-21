#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::InitGame(const int playerID, const bool zoneNames, const bool useCJWalk, const bool allowedWeapons, const bool limitGlobalChatRadius,
                                       const float globalChatRadius, const bool stuntBonus, const float nameTagDrawDistance, const bool disableEnterExits,
                                       const bool nameTagLOS, const bool manualVehicleEngineAndLight, const int spawnsAvailable,
                                       const bool showPlayerTags, const int showPlayerMarkers, const BYTE worldTime, const BYTE weather,
                                       const float gravity, const bool lanMode, const int deathDropMoney, const bool instagib, const int netModeNormalOnfootSendRate,
                                       const int netModeNormalIncarSendRate, const int netModeFiringSendRate, const int netModeSendMultiplier,
                                       const BYTE lagCompensation)
                {
                    Server *svr = server::GetServerInstance();

                    // TODO: Modify server config
                    RakNet::BitStream bsInitGame;
                    bsInitGame.WriteCompressed(zoneNames);                   // m_bZoneNames
                    bsInitGame.WriteCompressed(useCJWalk);                   // m_bUseCJWalk
                    bsInitGame.WriteCompressed(allowedWeapons);              // m_bAllowWeapons
                    bsInitGame.WriteCompressed(limitGlobalChatRadius);       // m_bLimitGlobalChatRadius
                    bsInitGame.Write(globalChatRadius);                      // m_fGlobalChatRadius
                    bsInitGame.WriteCompressed(stuntBonus);                  // bStuntBonus
                    bsInitGame.Write(nameTagDrawDistance);                   // m_fNameTagDrawDistance
                    bsInitGame.WriteCompressed(disableEnterExits);           // m_bDisableEnterExits
                    bsInitGame.WriteCompressed(nameTagLOS);                  // m_bNameTagLOS
                    bsInitGame.WriteCompressed(manualVehicleEngineAndLight); // m_bManualVehicleEngineAndLight
                    bsInitGame.Write(spawnsAvailable);                       // m_iSpawnsAvailable
                    bsInitGame.Write(playerID);                              // MyPlayerID
                    bsInitGame.WriteCompressed(showPlayerTags);              // m_bShowPlayerTags
                    bsInitGame.Write(showPlayerMarkers);                     // m_iShowPlayerMarkers
                    bsInitGame.Write(worldTime);                             // m_byteWorldTime
                    bsInitGame.Write(weather);                               // m_byteWeather
                    bsInitGame.Write(gravity);                               // m_fGravity
                    bsInitGame.WriteCompressed(lanMode);                     // bLanMode
                    bsInitGame.Write(deathDropMoney);                        // m_iDeathDropMoney
                    bsInitGame.WriteCompressed(instagib);                    // m_bInstagib

                    bsInitGame.Write(netModeNormalOnfootSendRate); // iNetModeNormalOnfootSendRate
                    bsInitGame.Write(netModeNormalIncarSendRate);  // iNetModeNormalIncarSendRate
                    bsInitGame.Write(netModeFiringSendRate);       // iNetModeFiringSendRate
                    bsInitGame.Write(netModeSendMultiplier);       // iNetModeSendMultiplier

                    bsInitGame.Write(lagCompensation); // m_bLagCompensation

                    bsInitGame.Write((BYTE)0); // unknown
                    bsInitGame.Write((BYTE)0); // unknown
                    bsInitGame.Write((BYTE)0); // unknown

                    BYTE bServerNameLen = (BYTE)strlen(svr->getInfo().hostname.c_str());
                    bsInitGame.Write(bServerNameLen);
                    bsInitGame.Write(svr->getInfo().hostname.c_str(), bServerNameLen);

                    BYTE vehModels[212];
                    memset(vehModels, 1, 212);
                    bsInitGame.Write((char *)&vehModels, 212);

                    svr->getRakServer()->RPC(&outgoing::RPC_InitGame, &bsInitGame, HIGH_PRIORITY, RELIABLE,
                                             0, svr->getRakServer()->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
                }
            }
        }
    }
}
