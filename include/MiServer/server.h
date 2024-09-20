#ifndef __MISERVER_SERVER_H
#define __MISERVER_SERVER_H
#include <stdint.h>
#include <MiServer/types.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct
    {
        char *hostname;
        char *gamemode;
        char *language;
        int maxplayers;
    } mimp_server_info_t;

    typedef struct
    {
        bool zoneNames;
        bool useCJWalk;
        bool allowedWeapons;
        bool limitGlobalChatRadius;
        float globalChatRadius;
        bool stuntBonus;
        float nameTagDrawDistance;
        bool disableEnterExits;
        bool nameTagLOS;
        bool manualVehicleEngineAndLight;
        int spawnsAvailable;
        bool showPlayerTags;
        int showPlayerMarkers;
        uint8_t worldTime;
        uint8_t weather;
        float gravity;
        bool lanMode;
        int deathDropMoney;
        bool instagib;
        int netModeNormalOnfootSendRate;
        int netModeNormalIncarSendRate;
        int netModeFiringSendRate;
        int netModeSendMultiplier;
        uint8_t lagCompensation;
    } mimp_server_config_t;

    mimp_server_info_t mimp_server_info__new(const char *hostname, const char *gamemode, const char *language, int maxplayers);
    mimp_server_config_t mimp_server_config__new(void);

    mimp_server_t mimp_server__new(mimp_server_info_t info, mimp_server_config_t config);
    int mimp_server__init(mimp_server_t server, uint16_t port);
    int mimp_server__serverTick(mimp_server_t server);
    int mimp_server__shutdown(mimp_server_t server);
    int mimp_server__destroy(mimp_server_t server);

    mimp_netgame_t mimp_server__getNetGame(mimp_server_t server);

#ifdef __cplusplus
}
#endif
#endif