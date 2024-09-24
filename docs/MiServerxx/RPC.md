# MiServer.xx RPC API
API Handler de RPC's

### Handler
Classe estatica que serve de Handler para RPC's.

#### Incomming
> RPC's vindos do client.

- *[ EnterVehicle ]*:
    - Chamado quando um Player tenta entrar em um carro.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void EnterVehicle(RPCParameters *rpcParams);
    ```

- *[ ExitVehicle ]*:
    - Chamado quando um Player tenta sair de um carro.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void ExitVehicle(RPCParameters *rpcParams);
    ```

- *[ VehicleDamaged ]*:
    - Chamado quando um veículo é danificado.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void VehicleDamaged(RPCParameters *rpcParams);
    ```

- *[ ScmEvent ]*:
    - Chamado quando um evento SCM ocorre.
    ```cpp
    static void ScmEvent(RPCParameters *rpcParams);
    ```

- *[ VehicleDestroyed ]*:
    - Chamado quando um veículo é destruído.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void VehicleDestroyed(RPCParameters *rpcParams);
    ```

- *[ SendSpawn ]*:
    - Chamado quando um Player envia um spawn.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void SendSpawn(RPCParameters *rpcParams);
    ```

- *[ ChatMessage ]*:
    - Chamado quando um Player envia uma mensagem de chat.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void ChatMessage(RPCParameters *rpcParams);
    ```

- *[ InteriorChangeNotification ]*:
    - Chamado quando um Player muda de interior.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void InteriorChangeNotification(RPCParameters *rpcParams);
    ```

- *[ DeathNotification ]*:
    - Chamado quando um Player morre.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void DeathNotification(RPCParameters *rpcParams);
    ```

- *[ SendCommand ]*:
    - Chamado quando um Player envia um comando.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void SendCommand(RPCParameters *rpcParams);
    ```

- *[ ClickPlayer ]*:
    - Chamado quando um Player clica em outro Player.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void ClickPlayer(RPCParameters *rpcParams);
    ```

- *[ DialogResponse ]*:
    - Chamado quando um Player responde a um diálogo.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void DialogResponse(RPCParameters *rpcParams);
    ```

- *[ ClientCheckResponse ]*:
    - Chamado quando um Player responde a uma verificação do cliente.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void ClientCheckResponse(RPCParameters *rpcParams);
    ```

- *[ GiveTakeDamage ]*:
    - Chamado quando um Player dá ou recebe dano.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void GiveTakeDamage(RPCParameters *rpcParams);
    ```

- *[ GiveActorDamage ]*:
    - Chamado quando um Player dá dano a um ator.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void GiveActorDamage(RPCParameters *rpcParams);
    ```

- *[ MapMarker ]*:
    - Chamado quando um Player coloca um marcador no mapa.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void MapMarker(RPCParameters *rpcParams);
    ```

- *[ RequestClass ]*:
    - Chamado quando um Player solicita uma classe.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void RequestClass(RPCParameters *rpcParams);
    ```

- *[ RequestSpawn ]*:
    - Chamado quando um Player solicita um spawn.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void RequestSpawn(RPCParameters *rpcParams);
    ```

- *[ MenuSelect ]*:
    - Chamado quando um Player seleciona uma opção no menu.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void MenuSelect(RPCParameters *rpcParams);
    ```

- *[ MenuQuit ]*:
    - Chamado quando um Player sai do menu.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void MenuQuit(RPCParameters *rpcParams);
    ```

- *[ SelectTextDraw ]*:
    - Chamado quando um Player seleciona um TextDraw.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void SelectTextDraw(RPCParameters *rpcParams);
    ```

- *[ PickedUpPickup ]*:
    - Chamado quando um Player pega um Pickup.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void PickedUpPickup(RPCParameters *rpcParams);
    ```

- *[ SelectObject ]*:
    - Chamado quando um Player seleciona um objeto.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void SelectObject(RPCParameters *rpcParams);
    ```

- *[ EditAttachedObject ]*:
    - Chamado quando um Player edita um objeto anexado.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void EditAttachedObject(RPCParameters *rpcParams);
    ```

- *[ EditObject ]*:
    - Chamado quando um Player edita um objeto.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void EditObject(RPCParameters *rpcParams);
    ```

- *[ UpdateScoresAndPings ]*:
    - Chamado quando os scores e pings são atualizados.
    ```cpp
    static void UpdateScoresAndPings(RPCParameters *rpcParams);
    ```

- *[ ClientJoin ]*:
    - Chamado quando um cliente se junta ao servidor.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void ClientJoin(RPCParameters *rpcParams);
    ```

- *[ NPCJoin ]*:
    - Chamado quando um NPC se junta ao servidor.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void NPCJoin(RPCParameters *rpcParams);
    ```

- *[ CameraTarget ]*:
    - Chamado quando um Player muda o alvo da câmera.
    - Caso não retornado, a ação não será executada.
    ```cpp
    static void CameraTarget(RPCParameters *rpcParams);
    ```

- *[ HandleUnsupported ]*:
    - Chamado quando um RPC não suportado é recebido.
    ```cpp
    static void HandleUnsupported(RPCParameters *rpcParams);
    ```

#### Outgoing
> RPC's enviados para o client.

> **NÃO É ACONSELHADO CHAMAR RPC'S DE FORMA BRUTA, CERTA VEZ QUE SÃO INDEPENDENTES E NÃO SINCRONIZAM COM O NETGAME**

- *[ SetCheckpoint ]*:
    - Define um checkpoint para o jogador.
    - `playerid`: O ID do jogador.
    - `x`: A coordenada x do checkpoint.
    - `y`: A coordenada y do checkpoint.
    - `z`: A coordenada z do checkpoint.
    - `sz`: O tamanho do checkpoint.
    ```cpp
    static void SetCheckpoint(const int playerid, const float x, const float y, const float z, const float sz);
    ```

- *[ SetPlayerFacingAngle ]*:
    - Define o ângulo de visão do jogador.
    - `playerid`: O ID do jogador.
    - `a`: O ângulo de visão.
    ```cpp
    static void SetPlayerFacingAngle(const int playerid, const float a);
    ```

- *[ ServerJoin ]*:
    - Chamado quando o servidor se junta.
    ```cpp
    static void ServerJoin(void);
    ```

- *[ ServerQuit ]*:
    - Chamado quando o servidor sai.
    ```cpp
    static void ServerQuit(void);
    ```

- *[ InitGame ]*:
    - Inicializa o jogo para o jogador.
    - `playerID`: O ID do jogador.
    - `zoneNames`: Indica se os nomes das zonas estão ativados.
    - `useCJWalk`: Indica se o jogador usa a caminhada CJ.
    - `allowedWeapons`: Indica se as armas são permitidas.
    - `limitGlobalChatRadius`: Indica se o raio do chat global é limitado.
    - `globalChatRadius`: O raio do chat global.
    - `stuntBonus`: Indica se o bônus de acrobacia está ativado.
    - `nameTagDrawDistance`: A distância de desenho do nome.
    - `disableEnterExits`: Indica se as entradas e saídas estão desativadas.
    - `nameTagLOS`: Indica se o nome está visível na linha de visão.
    - `manualVehicleEngineAndLight`: Indica se o motor e a luz do veículo são manuais.
    - `spawnsAvailable`: O número de spawns disponíveis.
    - `showPlayerTags`: Indica se as tags dos jogadores estão visíveis.
    - `showPlayerMarkers`: O modo de exibição dos marcadores dos jogadores.
    - `worldTime`: O tempo do mundo.
    - `weather`: O clima.
    - `gravity`: A gravidade.
    - `lanMode`: Indica se o modo LAN está ativado.
    - `deathDropMoney`: O dinheiro dropado na morte.
    - `instagib`: Indica se o instagib está ativado.
    - `netModeNormalOnfootSendRate`: A taxa de envio normal a pé.
    - `netModeNormalIncarSendRate`: A taxa de envio normal no carro.
    - `netModeFiringSendRate`: A taxa de envio de disparo.
    - `netModeSendMultiplier`: O multiplicador de envio.
    - `lagCompensation`: A compensação de lag.
    ```cpp
    static void InitGame(const int playerID, const bool zoneNames, const bool useCJWalk, const bool allowedWeapons, const bool limitGlobalChatRadius,
                         const float globalChatRadius, const bool stuntBonus, const float nameTagDrawDistance, const bool disableEnterExits,
                         const bool nameTagLOS, const bool manualVehicleEngineAndLight, const int spawnsAvailable,
                         const bool showPlayerTags, const int showPlayerMarkers, const BYTE worldTime, const BYTE weather,
                         const float gravity, const bool lanMode, const int deathDropMoney, const bool instagib, const int netModeNormalOnfootSendRate,
                         const int netModeNormalIncarSendRate, const int netModeFiringSendRate, const int netModeSendMultiplier,
                         const BYTE lagCompensation);
    ```

- *[ UpdateScoresAndPings ]*:
    - Atualiza os scores e pings.
    ```cpp
    static void UpdateScoresAndPings(void);
    ```

- *[ SetPlayerPos ]*:
    - Define a posição do jogador.
    - `playerid`: O ID do jogador.
    - `x`: A coordenada x da posição.
    - `y`: A coordenada y da posição.
    - `z`: A coordenada z da posição.
    ```cpp
    static void SetPlayerPos(const int playerid, const float x, const float y, const float z);
    ```

- *[ SetPlayerSkin ]*:
    - Define a skin do jogador.
    - `playerid`: O ID do jogador.
    - `skinid`: O ID da skin.
    ```cpp
    static void SetPlayerSkin(const int playerid, const int skinid);
    ```

- *[ SetPlayerHealth ]*:
    - Define a saúde do jogador.
    - `playerid`: O ID do jogador.
    - `value`: O valor da saúde.
    ```cpp
    static void SetPlayerHealth(const int playerid, const float value);
    ```

- *[ SetPlayerArmour ]*:
    - Define a armadura do jogador.
    - `playerid`: O ID do jogador.
    - `value`: O valor da armadura.
    ```cpp
    static void SetPlayerArmour(const int playerid, const float value);
    ```

- *[ WorldPlayerAdd ]*:
    - Adiciona um jogador ao mundo.
    ```cpp
    static void WorldPlayerAdd(void);
    ```

- *[ WorldPlayerRemove ]*:
    - Remove um jogador do mundo.
    ```cpp
    static void WorldPlayerRemove(void);
    ```

- *[ SendClientMessage ]*:
    - Envia uma mensagem para o cliente.
    - `playerid`: O ID do jogador.
    - `color`: A cor da mensagem.
    - `messageLength`: O comprimento da mensagem.
    - `message`: O texto da mensagem.
    ```cpp
    static void SendClientMessage(const int playerid, const int color, const int messageLength, const char *message);
    ```

- *[ SetPlayerColor ]*:
    - Define a cor do jogador.
    - `playerid`: O ID do jogador.
    - `color`: A cor a ser definida.
    ```cpp
    static void SetPlayerColor(const int playerid, const unsigned long color);
    ```

- *[ SetSpawnInfo ]*:
    - Define as informações de spawn.
    ```cpp
    static void SetSpawnInfo(void);
    ```

- *[ RequestClass ]*:
    - Solicita uma classe.
    ```cpp
    static void RequestClass(void);
    ```

- *[ RequestSpawn ]*:
    - Solicita um spawn.
    ```cpp
    static void RequestSpawn(void);
    ```

- *[ PlayerEnterVehicle ]*:
    - Chamado quando um jogador entra em um veículo.
    - `playerid`: O ID do jogador.
    - `vehicleid`: O ID do veículo.
    - `passenger`: Indica se o jogador é passageiro.
    ```cpp
    static void PlayerEnterVehicle(const WORD playerid, const WORD vehicleid, const BYTE passenger);
    ```

- *[ PlayerExitVehicle ]*:
    - Chamado quando um jogador sai de um veículo.
    - `playerid`: O ID do jogador.
    - `vehicleid`: O ID do veículo.
    ```cpp
    static void PlayerExitVehicle(const WORD playerid, const WORD vehicleid);
    ```

- *[ WorldVehicleAdd ]*:
    - Adiciona um veículo ao mundo.
    - `veh`: O ponteiro para o veículo.
    - `playerid`: O ID do jogador.
    ```cpp
    static void WorldVehicleAdd(CVehicle *veh, const int playerid);
    ```

- *[ WorldVehicleRemove ]*:
    - Remove um veículo do mundo.
    - `idx`: O índice do veículo.
    - `playerid`: O ID do jogador.
    ```cpp
    static void WorldVehicleRemove(const WORD idx, const int playerid);
    ```

- *[ ConnectionRejected ]*:
    - Chamado quando a conexão é rejeitada.
    ```cpp
    static void ConnectionRejected(void);
    ```