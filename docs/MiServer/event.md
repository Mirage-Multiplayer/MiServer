# MiServer.xx Event API
API de eventos do MiServerxx

### EventPool
> ** Importante ler mais em [MiServer.xx](../MiServerxx/event.md) **

### Documentação da C-API

#### *[ Server Init ]*:
- Chamado quando o servidor inicia.
- Não recebe parâmetros.
```cpp
void mimp_server_event__onServerInit(mimp_core_t core, int (*cb)(void));
```

#### *[ Server Exit ]*:
- Chamado quando o servidor desliga.
- Não recebe parâmetros.
```cpp
void mimp_server_event__onServerExit(mimp_core_t core, int (*cb)(void));
```

#### *[ Player Connect ]*:
- Chamado quando um player conecta.
- Recebe o player que conectou.
```cpp
void mimp_server_event__onPlayerConnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player));
```

#### *[ Player Disconnect ]*:
- Chamado quando um player desconecta.
- Recebe o player que desconectou e a razão da desconexão.
```cpp
void mimp_server_event__onPlayerDisconnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, int reason));
```

#### *[ Player Spawn ]*:
- Chamado quando um player respawna.
- Recebe o player que respawnou.
```cpp
void mimp_server_event__onPlayerSpawn(mimp_core_t c, int (*cb)(mimp_netgame_player_t player));
```

#### *[ Player Text ]*:
- Chamado quando um player envia uma mensagem de texto.
- Recebe o player que enviou a mensagem e o texto enviado.
```cpp
void mimp_server_event__onPlayerText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *text));
```

#### *[ Player Command Text ]*:
- Chamado quando um player envia um comando de texto.
- Recebe o player que enviou o comando e o comando enviado.
```cpp
void mimp_server_event__onPlayerCommandText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *cmdtext));
```