# MiServer.xx Server API
API para gerenciamento do servidor.

### Estruturas e Classes

#### Estrutura
> Estruturas utilizadas no servidor.

- *[ ServerInfo ]*:
    - Estrutura que contém as informações do servidor.
    - **Construtor**:
        - `ServerInfo(const char *hostname, const char *gamemode, const char *lang, const unsigned int max_players)`: Inicializa a estrutura com as informações do servidor.
            - `hostname`: O nome do host do servidor.
            - `gamemode`: O modo de jogo do servidor.
            - `lang`: O idioma do servidor.
            - `max_players`: O número máximo de jogadores no servidor.

#### Classes
> Classes utilizadas no servidor.

- *[ CServer ]*:
    - Classe que representa o servidor.
    - **Construtores**:
        - `CServer(const ServerInfo &info)`: Construtor que inicializa o servidor com as informações fornecidas.
            - `info`: As informações do servidor.
        - `CServer(const ServerInfo &info, const ServerConfig &config)`: Construtor que inicializa o servidor com as informações e configuração fornecidas.
            - `info`: As informações do servidor.
            - `config`: A configuração do servidor.
    - **Destrutor**:
        - `~CServer()`: Destrutor da classe `CServer`.
    - **Métodos Públicos**:
        - *[ Init ]*:
            - Inicializa o servidor na porta especificada.
            - `port`: A porta na qual o servidor será inicializado.
            - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
            ```cpp
            int Init(uint16_t port);
            ```
        - *[ Shutdown ]*:
            - Desliga o servidor e mata a instância do servidor.
            - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
            ```cpp
            int Shutdown(void);
            ```
        - *[ ServerTick ]*:
            - Processa o Tick do servidor (atualização).
            - Deve ser chamado dentro de um loop infinito.
            - **Retorno**: Um inteiro indicando o sucesso ou falha da operação.
            ```cpp
            int ServerTick(void);
            ```
        - *[ getInfo ]*:
            - Retorna as informações do servidor.
            - **Retorno**: As informações do servidor.
            ```cpp
            inline const ServerInfo getInfo(void) const;
            ```
        - *[ getConfig ]*:
            - Retorna a configuração do servidor.
            - **Retorno**: A configuração do servidor.
            ```cpp
            inline const ServerConfig getConfig(void) const;
            ```
        - *[ GetNetGame ]*:
            - Retorna a instância do jogo em rede do servidor.
            - **Retorno**: Um ponteiro para a instância do jogo em rede.
            ```cpp
            inline mimp::CNetGame *GetNetGame();
            ```
        - *[ getRakServer ]*:
            - Retorna a instância da interface RakServer do servidor.
            - **Retorno**: Um ponteiro para a instância da interface RakServer.
            ```cpp
            inline RakServerInterface *getRakServer(void) const;
            ```
        - *[ getEventPool ]*:
            - Retorna a instância do pool de eventos do servidor.
            - **Retorno**: Um ponteiro para a instância do pool de eventos.
            ```cpp
            inline mimp::internal::event::CEventPool *getEventPool(void) const;
            ```