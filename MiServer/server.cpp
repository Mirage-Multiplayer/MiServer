#include <MiServer/server.h>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/server/Server.hpp>
#include <MiServerxx/server/ServerConfig.hpp>

mimp_server_info_t mimp_server_info__new(const char *hostname, const char *gamemode, const char *language, int maxplayers)
{
    mimp_server_info_t info;
    info.hostname = nullptr;
    info.gamemode = nullptr;
    info.language = nullptr;

    info.hostname = (char *)malloc(strlen(hostname) + 1);
    if (info.hostname == nullptr)
    {
        return info; // Return early if allocation fails
    }
    strcpy(info.hostname, hostname);

    info.gamemode = (char *)malloc(strlen(gamemode) + 1);
    if (info.gamemode == nullptr)
    {
        free(info.hostname); // Free previously allocated memory
        return info;         // Return early if allocation fails
    }
    strcpy(info.gamemode, gamemode);

    info.language = (char *)malloc(strlen(language) + 1);
    if (info.language == nullptr)
    {
        free(info.hostname); // Free previously allocated memory
        free(info.gamemode); // Free previously allocated memory
        return info;         // Return early if allocation fails
    }
    strcpy(info.language, language);

    info.maxplayers = maxplayers;
    return info;
}
mimp_server_config_t mimp_server_config__new(void)
{
    mimp::ServerConfig cfg;
    mimp_server_config_t config;
    config.zoneNames = cfg.zoneNames;
    config.useCJWalk = cfg.useCJWalk;
    config.allowedWeapons = cfg.allowedWeapons;
    config.limitGlobalChatRadius = cfg.limitGlobalChatRadius;
    config.globalChatRadius = cfg.globalChatRadius;
    config.stuntBonus = cfg.stuntBonus;
    config.nameTagDrawDistance = cfg.nameTagDrawDistance;
    config.disableEnterExits = cfg.disableEnterExits;
    config.nameTagLOS = cfg.nameTagLOS;
    config.manualVehicleEngineAndLight = cfg.manualVehicleEngineAndLight;
    config.spawnsAvailable = cfg.spawnsAvailable;
    config.showPlayerTags = cfg.showPlayerTags;
    config.showPlayerMarkers = cfg.showPlayerMarkers;
    config.worldTime = cfg.worldTime;
    config.weather = cfg.weather;
    config.gravity = cfg.gravity;
    config.lanMode = cfg.lanMode;
    config.deathDropMoney = cfg.deathDropMoney;
    config.instagib = cfg.instagib;
    config.netModeNormalOnfootSendRate = cfg.netModeNormalOnfootSendRate;
    config.netModeNormalIncarSendRate = cfg.netModeNormalIncarSendRate;
    config.netModeFiringSendRate = cfg.netModeFiringSendRate;
    config.netModeSendMultiplier = cfg.netModeSendMultiplier;
    config.lagCompensation = cfg.lagCompensation;
    return config;
}

static mimp::ServerConfig __toServerConfig(mimp_server_config_t config)
{
    mimp::ServerConfig cfg;
    cfg.zoneNames = config.zoneNames;
    cfg.useCJWalk = config.useCJWalk;
    cfg.allowedWeapons = config.allowedWeapons;
    cfg.limitGlobalChatRadius = config.limitGlobalChatRadius;
    cfg.globalChatRadius = config.globalChatRadius;
    cfg.stuntBonus = config.stuntBonus;
    cfg.nameTagDrawDistance = config.nameTagDrawDistance;
    cfg.disableEnterExits = config.disableEnterExits;
    cfg.nameTagLOS = config.nameTagLOS;
    cfg.manualVehicleEngineAndLight = config.manualVehicleEngineAndLight;
    cfg.spawnsAvailable = config.spawnsAvailable;
    cfg.showPlayerTags = config.showPlayerTags;
    cfg.showPlayerMarkers = config.showPlayerMarkers;
    cfg.worldTime = config.worldTime;
    cfg.weather = config.weather;
    cfg.gravity = config.gravity;
    cfg.lanMode = config.lanMode;
    cfg.deathDropMoney = config.deathDropMoney;
    cfg.instagib = config.instagib;
    cfg.netModeNormalOnfootSendRate = config.netModeNormalOnfootSendRate;
    cfg.netModeNormalIncarSendRate = config.netModeNormalIncarSendRate;
    cfg.netModeFiringSendRate = config.netModeFiringSendRate;
    cfg.netModeSendMultiplier = config.netModeSendMultiplier;
    cfg.lagCompensation = config.lagCompensation;
    return cfg;
}

static mimp::ServerInfo __toServerInfo(mimp_server_info_t info)
{
    mimp::ServerInfo inf(info.hostname, info.gamemode, info.language, info.maxplayers);
    return inf;
}

mimp_server_t mimp_server__new(mimp_server_info_t info, mimp_server_config_t config)
{
    void *server = new mimp::CServer(__toServerInfo(info), __toServerConfig(config));
    return server;
}

int mimp_server__init(mimp_server_t server, uint16_t port)
{
    reinterpret_cast<mimp::CServer *>(server)->Init(port);
    return 1;
}

int mimp_server__serverTick(mimp_server_t server)
{
    return reinterpret_cast<mimp::CServer *>(server)->ServerTick();
}

int mimp_server__shutdown(mimp_server_t server)
{
    return reinterpret_cast<mimp::CServer *>(server)->Shutdown();
}

int mimp_server__destroy(mimp_server_t server)
{
    delete (reinterpret_cast<mimp::CServer *>(server));
    return 1;
}

mimp_netgame_t mimp_server__getNetGame(mimp_server_t server)
{
    return reinterpret_cast<mimp::CServer *>(server)->GetNetGame();
}