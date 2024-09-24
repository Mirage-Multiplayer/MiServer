# MiServer.xx Event API
API de eventos do MiServerxx

### EventPool
[ **CEventPool** ]:

Classe que abstrai uma pool de eventos, todos os eventos são armazenados nela, iniciada quando o servidor inicia, e destruida quando é desligado.

- eventos pré-definidos.
- chamada: On + EventName e.g OnServerInit
- Emit events with Emit method
    - **uint16_t** event ID
    - **void_ptr** context

### EventTypes
[ **Event ID's** ]:

Enum contendo ID's dos eventos

- SERVER_EVENT_SERVERINIT = 0,
- SERVER_EVENT_SERVEREXIT = 1,
- SERVER_EVENT_PLAYERCONNECT = 2,
- SERVER_EVENT_PLAYERDISCONNECT = 3,
- SERVER_EVENT_PLAYERSPAWN = 4,
- SERVER_EVENT_PLAYERDEATH = 5,
- SERVER_EVENT_PLAYERTEXT = 6,
- SERVER_EVENT_COMMANDTEXT = 7,
- SERVER_EVENT_PLAYERUPDATE = 8

[ **Event Functions** ]:

Tipos de funções e uma struct contendo os parâmetros da mesma, e.g. context.

- *[ Server Init ]*:
    - chamado quando o servidor inicia
    - Não recebe parâmetros
    ```cpp
    using OnServerInit_t = std::function<int()>;
    ```
- *[ Server Exit ]*:
    - chamado quando o servidor desliga
    - Não recebe parâmetros
    ```cpp
    using OnServerExit_t = std::function<int()>;
    ```
- *[ Player Connect ]*:
    - chamado quando um player conecta
    - recebe o player que conectou
    ```cpp
    using OnPlayerConnect_t = std::function<int(CPlayer *)>;
    using OnPlayerConnect_params = struct
    {
        CPlayer *player;
    };
    ```
- *[ Player Disconnect ]*:
    - chamado quando um player desconecta
    - recebe o player que desconectou e a razão da desconexão
    ```cpp
    using OnPlayerDisconnect_t = std::function<int(CPlayer *, const int)>;
    using OnPlayerDisconnect_params = struct
    {
        CPlayer *player;
        const int reason;
    };
    ```
- *[ Player Spawn ]*:
    - chamado quando um player respawna
    - recebe o player que respawnou
    ```cpp
    using OnPlayerSpawn_t = std::function<int(CPlayer *)>;
    using OnPlayerSpawn_params = struct
    {
        CPlayer *player;
    };
    ```
- *[ Player Update ]*:
    - chamado quando um player é atualizado
    - recebe o player que foi atualizado
    ```cpp
    using OnPlayerUpdate_t = std::function<int(CPlayer *)>;
    using OnPlayerUpdate_params = struct
    {
        CPlayer *player;
    };
    ```
- *[ Player Death ]*:
    - chamado quando um player morre
    - recebe o player que morreu, o player que matou e a razão da morte
    ```cpp
    using OnPlayerDeath_t = std::function<int(CPlayer *, CPlayer *, const int)>;
    using OnPlayerDeath_params = struct
    {
        CPlayer *player;
        CPlayer *killer;
        const int reason;
    };
    ```
- *[ Vehicle Spawn ]*:
    - chamado quando um veículo respawna
    - recebe o veículo que respawnou
    ```cpp
    using OnVehicleSpawn_t = std::function<int(CVehicle *)>;
    using OnVehicleSpawn_params = struct
    {
        CVehicle *vehicle;
    };
    ```
- *[ Vehicle Death ]*:
    - chamado quando um veículo é destruído
    - recebe o veículo que foi destruído e o player que destruiu
    ```cpp
    using OnVehicleDeath_t = std::function<int(CVehicle *, CPlayer *)>;
    using OnVehicleDeath_params = struct
    {
        CVehicle *vehicle;
        CPlayer *killer;
    };
    ```
- *[ Player Text ]*:
    - chamado quando um player envia uma mensagem de texto
    - recebe o player que enviou a mensagem e o texto enviado
    ```cpp
    using OnPlayerText_t = std::function<int(CPlayer *, const char *)>;
    using OnPlayerText_params = struct
    {
        CPlayer *player;
        const char *text;
    };
    ```
- *[ Player Command Text ]*:
    - chamado quando um player envia um comando de texto
    - recebe o player que enviou o comando e o comando enviado
    ```cpp
    using OnPlayerCommandText_t = std::function<int(CPlayer *, const char *)>;
    using OnPlayerCommandText_params = struct
    {
        CPlayer *player;
        const char *cmd;
    };
    ```
- *[ Player Request Class ]*:
    - chamado quando um player solicita uma classe
    - recebe o player que solicitou a classe e o ID da classe solicitada
    ```cpp
    using OnPlayerRequestClass_t = std::function<int(CPlayer *, const int)>;
    using OnPlayerRequestClass_params = struct
    {
        CPlayer *player;
        const int classid;
    };
    ```
- *[ Player Enter Vehicle ]*:
    - chamado quando um player entra em um veículo
    - recebe o player que entrou no veículo e o veículo
    ```cpp
    using OnPlayerEnterVehicle_t = std::function<int(CPlayer *, CVehicle *)>;
    using OnPlayerEnterVehicle_params = struct
    {
        CPlayer *player;
        CVehicle *vehicle;
    };
    ```
- *[ Player Exit Vehicle ]*:
    - chamado quando um player sai de um veículo
    - recebe o player que saiu do veículo e o veículo
    ```cpp
    using OnPlayerExitVehicle_t = std::function<int(CPlayer *, CVehicle *)>;
    using OnPlayerExitVehicle_params = struct
    {
        CPlayer *player;
        CVehicle *vehicle;
    };
    ```