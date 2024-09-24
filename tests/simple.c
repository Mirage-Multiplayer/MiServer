#include <stdio.h>
#include <MiServer/MiServer.h>

mimp_core_t server = NULL;

int onServerInit(void)
{
    printf("Server initialized\n");
    return 0;
}

int onServerExit(void)
{
    printf("Server exited\n");
    return 0;
}

int onPlayerConnect(mimp_netgame_player_t player)
{
    const int id = mimp_netgame_player__getId(player);
    printf("Player ID %d connected\n", id);
    return 0;
}

int onPlayerText(mimp_netgame_player_t player, const char *text)
{
    const int id = mimp_netgame_player__getId(player);
    mimp_netgame_player__clientMessage(player, 0xFFFFFFFF, text);
    printf("Player ID %d said: %s\n", id, text);
    return 0;
}

int onPlayerCommandText(mimp_netgame_player_t player, const char *cmdtext)
{
    const int id = mimp_netgame_player__getId(player);
    mimp_netgame_t netgame = mimp_core__getNetGame(server);
    float x, y, z, f;
    mimp_netgame_player__getPos(player, &x, &y, &z);
    mimp_netgame_player__getRotation(player, &f);

    int model = 411;
    if (sscanf(cmdtext, "/vehicle %d", &model) == 1)
    {
        mimp_netgame_vehicle__create(netgame, model, x, y, z, f, -1, -1, 0, 0, 0, 0);
    }
    return 0;
}

int main(void)
{
    mimp_server_info_t info = mimp_server_info__new("hostname", "gamemode", "language", 32);
    mimp_server_config_t config = mimp_server_config__new();
    server = mimp_core__new(info, config);
    mimp_server_event__onServerInit(server, onServerInit);
    mimp_server_event__onServerExit(server, onServerExit);
    mimp_server_event__onPlayerConnect(server, onPlayerConnect);
    mimp_server_event__onPlayerText(server, onPlayerText);
    mimp_server_event__onPlayerCommandText(server, onPlayerCommandText);

    mimp_core__run(server, 7777);
    while (1)
    {
        mimp_core__proccessTick(server);
    }
    return 1;
}