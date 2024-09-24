#ifndef __MISERVER_CORE_H
#define __MISERVER_CORE_H
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

    mimp_core_t mimp_core__new(mimp_server_info_t info, mimp_server_config_t config);
    int mimp_core__run(mimp_core_t core, uint16_t port);
    int mimp_core__proccessTick(mimp_core_t core);
    int mimp_core__shutdown(mimp_core_t core);
    int mimp_core__destroy(mimp_core_t core);

    mimp_netgame_t mimp_core__getNetGame(mimp_core_t core);

#ifdef __cplusplus
}
#endif
#endif