# MiServer Server API

### Estruturas e Funções do Servidor

#### Estruturas

- *[ mimp_server_info_t ]*:
    - Estrutura que contém as informações do servidor.
    - **Campos**:
        - `hostname`: O nome do host do servidor.
        - `gamemode`: O modo de jogo do servidor.
        - `language`: O idioma do servidor.
        - `maxplayers`: O número máximo de jogadores no servidor.

- *[ mimp_server_config_t ]*:
    - Estrutura que contém a configuração do servidor.
    - **Campos**:
        - `zoneNames`: Indica se os nomes das zonas são mostrados.
        - `useCJWalk`: Define se o modo de movimento do CJ é ativado.
        - `allowedWeapons`: Permite ou proíbe armas.
        - `limitGlobalChatRadius`: Define se o chat global é limitado por um raio.
        - `globalChatRadius`: O raio de alcance do chat global.
        - `stuntBonus`: Habilita ou desabilita bônus de acrobacias.
        - `nameTagDrawDistance`: Distância de exibição das etiquetas de nome.
        - `disableEnterExits`: Desabilita a funcionalidade de entrada e saída.
        - `nameTagLOS`: Controla se as etiquetas de nome são exibidas apenas quando visíveis.
        - `manualVehicleEngineAndLight`: Define se motores e luzes de veículos são controlados manualmente.
        - `spawnsAvailable`: Número de pontos de spawn disponíveis.
        - `showPlayerTags`: Indica se as etiquetas de nome dos jogadores são exibidas.
        - `showPlayerMarkers`: Configuração de exibição dos marcadores de jogadores.
        - `worldTime`: Hora do mundo do jogo.
        - `weather`: Clima do jogo.
        - `gravity`: Valor da gravidade no jogo.
        - `lanMode`: Define se o servidor opera no modo LAN.
        - `deathDropMoney`: Quantia de dinheiro derrubada ao morrer.
        - `instagib`: Ativa ou desativa o instagib (morte instantânea).
        - `netModeNormalOnfootSendRate`: Taxa de envio de dados para jogadores a pé.
        - `netModeNormalIncarSendRate`: Taxa de envio de dados para jogadores em veículos.
        - `netModeFiringSendRate`: Taxa de envio de dados para ações de disparo.
        - `netModeSendMultiplier`: Multiplicador para a taxa de envio.
        - `lagCompensation`: Define se a compensação de lag está ativada.

### Funções

- *[ mimp_server_info__new ]*:
    - Cria uma nova instância da estrutura de informações do servidor.
    - **Parâmetros**:
        - `hostname`: O nome do host do servidor.
        - `gamemode`: O modo de jogo do servidor.
        - `language`: O idioma do servidor.
        - `maxplayers`: O número máximo de jogadores no servidor.
    - **Retorno**: Uma instância inicializada de `mimp_server_info_t`.
    ```c
    mimp_server_info_t mimp_server_info__new(const char *hostname, const char *gamemode, const char *language, int maxplayers);
    ```

- *[ mimp_server_config__new ]*:
    - Cria uma nova instância da estrutura de configuração do servidor com valores padrão.
    - **Retorno**: Uma instância inicializada de `mimp_server_config_t`.
    ```c
    mimp_server_config_t mimp_server_config__new(void);
    ```

- *[ mimp_core__new ]*:
    - Cria uma nova instância do servidor.
    - **Parâmetros**:
        - `info`: As informações do servidor.
        - `config`: A configuração do servidor.
    - **Retorno**: Uma instância de `mimp_core_t` representando o servidor.
    ```c
    mimp_core_t mimp_core__new(mimp_server_info_t info, mimp_server_config_t config);
    ```

- *[ mimp_core__run ]*:
    - Inicializa e executa o servidor na porta especificada.
    - **Parâmetros**:
        - `core`: A instância do servidor.
        - `port`: A porta na qual o servidor será executado.
    - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
    ```c
    int mimp_core__run(mimp_core_t core, uint16_t port);
    ```

- *[ mimp_core__proccessTick ]*:
    - Processa a atualização do servidor (tick).
    - **Parâmetros**:
        - `core`: A instância do servidor.
    - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
    ```c
    int mimp_core__proccessTick(mimp_core_t core);
    ```

- *[ mimp_core__shutdown ]*:
    - Desliga o servidor e encerra a instância.
    - **Parâmetros**:
        - `core`: A instância do servidor.
    - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
    ```c
    int mimp_core__shutdown(mimp_core_t core);
    ```

- *[ mimp_core__destroy ]*:
    - Libera recursos associados à instância do servidor.
    - **Parâmetros**:
        - `core`: A instância do servidor.
    - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
    ```c
    int mimp_core__destroy(mimp_core_t core);
    ```

- *[ mimp_core__getNetGame ]*:
    - Retorna a instância do jogo em rede associada ao servidor.
    - **Parâmetros**:
        - `core`: A instância do servidor.
    - **Retorno**: Um ponteiro para a instância do jogo em rede (`mimp_netgame_t`).
    ```c
    mimp_netgame_t mimp_core__getNetGame(mimp_core_t core);
    ```