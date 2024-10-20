# MiServer.xx NetGame API

### NetGame
[ **CNetGame** ]:

Uma classe que gerencia as entidades do servidor, inicializada com o numero maximo de cada entidade permitida no servidor.

- *[ Player Pool ]*:
    - Uma pool de players

- *[ Vehicle Pool ]*:
    - Uma pool de veiculos

### Pool
[ **CPool** ]:

Classe Pool para as entidades.

#### Template Parameters
- `element`: O tipo de elemento que a pool irá gerenciar.

#### Construtor
- `CPool(uint16_t size)`: Inicializa a pool com um tamanho máximo especificado.
    - `size`: O número máximo de elementos que a pool pode conter.

#### Métodos Públicos

- *[ GetMax ]*:
    - Retorna o tamanho máximo da pool.
    - **Retorno**: O tamanho máximo da pool.
    ```cpp
    uint16_t GetMax(void);
    ```

- *[ DeleteAt ]*:
    - Deleta o elemento na posição especificada.
    - `idx`: O índice do elemento a ser deletado.
    - **Nota**: Se o índice for inválido, a função não faz nada.
    ```cpp
    void DeleteAt(const uint16_t idx);
    ```

- *[ InsertAt ]*:
    - Insere um elemento na posição especificada.
    - `idx`: O índice onde o elemento será inserido.
    - `elem`: O ponteiro para o elemento a ser inserido.
    - **Retorno**: `true` se a inserção for bem-sucedida, `false` caso contrário.
    ```cpp
    bool InsertAt(const uint16_t idx, element *elem);
    ```

- *[ Insert ]*:
    - Insere um elemento na primeira posição disponível.
    - `elem`: O ponteiro para o elemento a ser inserido.
    - **Retorno**: O índice onde o elemento foi inserido, ou `-1` se a pool estiver cheia.
    ```cpp
    int Insert(element *elem);
    ```

- *[ GetAt ]*:
    - Retorna o elemento na posição especificada.
    - `idx`: O índice do elemento a ser retornado.
    - **Retorno**: O ponteiro para o elemento na posição especificada, ou `nullptr` se o índice for inválido.
    ```cpp
    element *GetAt(uint16_t idx);
    ```

- *[ begin ]*:
    - Retorna um iterador para o início da pool.
    - **Retorno**: Um iterador para o início da pool.
    ```cpp
    auto begin();
    ```

- *[ end ]*:
    - Retorna um iterador para o final da pool.
    - **Retorno**: Um iterador para o final da pool.
    ```cpp
    auto end();
    ```

- *[ begin (const) ]*:
    - Retorna um iterador constante para o início da pool.
    - **Retorno**: Um iterador constante para o início da pool.
    ```cpp
    auto begin() const;
    ```

- *[ end (const) ]*:
    - Retorna um iterador constante para o final da pool.
    - **Retorno**: Um iterador constante para o final da pool.
    ```cpp
    auto end() const;
    ```

### Player
[ **CPlayer** ]:

Classe que representa um objeto jogador.

#### Construtor
- `CPlayer(PlayerID rakPlayerID, WORD playerID, const char *nickname)`: Construtor da classe `CPlayer`.
    - `rakPlayerID`: O ID do jogador no RakNet.
    - `playerID`: O ID do jogador na pool de jogadores.
    - `nickname`: O apelido do jogador.

#### Métodos Públicos

- *[ getPlayerId ]*:
    - Retorna o ID do jogador.
    - **Retorno**: O ID do jogador na pool de jogadores.
    ```cpp
    inline const WORD getPlayerId(void) const;
    ```

- *[ getRakPlayerId ]*:
    - Retorna o ID do jogador no RakNet.
    - **Retorno**: O ID do jogador no RakNet.
    ```cpp
    inline const PlayerID getRakPlayerId(void) const;
    ```

- *[ getNickName ]*:
    - Retorna o apelido do jogador.
    - **Retorno**: O apelido do jogador.
    ```cpp
    inline const std::string getNickName(void) const;
    ```

- *[ getHealth ]*:
    - Retorna a saúde do jogador.
    - **Retorno**: A saúde do jogador.
    ```cpp
    inline const float getHealth(void) const;
    ```

- *[ getArmour ]*:
    - Retorna a armadura do jogador.
    - **Retorno**: A armadura do jogador.
    ```cpp
    inline const float getArmour(void) const;
    ```

- *[ getInteriorId ]*:
    - Retorna o ID do interior do jogador.
    - **Retorno**: O ID do interior do jogador.
    ```cpp
    inline const int getInteriorId(void) const;
    ```

- *[ getIP ]*:
    - Retorna o endereço IP do jogador.
    - **Retorno**: O endereço IP do jogador como uma string.
    ```cpp
    inline const std::string getIP(void) const;
    ```

- *[ getClientPort ]*:
    - Retorna o número da porta do cliente.
    - **Retorno**: O número da porta do cliente.
    ```cpp
    inline const uint16_t getClientPort(void) const;
    ```

- *[ getScore ]*:
    - Retorna a pontuação do jogador.
    - **Retorno**: A pontuação do jogador como um inteiro.
    ```cpp
    inline const int getScore(void) const;
    ```

- *[ getPing ]*:
    - Retorna o ping do jogador.
    - **Retorno**: O ping do jogador em milissegundos.
    ```cpp
    inline const DWORD getPing(void) const;
    ```

- *[ getCurrentVehicle ]*:
    - Retorna o ID do veículo em que o jogador está atualmente.
    - **Retorno**: O ID do veículo atual.
    ```cpp
    inline const WORD getCurrentVehicle(void) const;
    ```

- *[ getSkin ]*:
    - Retorna o ID da skin do jogador.
    - **Retorno**: O ID da skin do jogador como um inteiro.
    ```cpp
    inline const int getSkin(void) const;
    ```

- *[ getSpawn ]*:
    - Retorna a posição de spawn do jogador.
    - `x`: Referência para a coordenada x da posição de spawn.
    - `y`: Referência para a coordenada y da posição de spawn.
    - `z`: Referência para a coordenada z da posição de spawn.
    ```cpp
    inline void getSpawn(float &x, float &y, float &z) const;
    ```

- *[ getPos ]*:
    - Retorna a posição atual do jogador.
    - `x`: Referência para a coordenada x da posição atual.
    - `y`: Referência para a coordenada y da posição atual.
    - `z`: Referência para a coordenada z da posição atual.
    ```cpp
    inline void getPos(float &x, float &y, float &z) const;
    ```

- *[ getRotation ]*:
    - Retorna a rotação do jogador.
    - **Retorno**: A rotação do jogador em graus.
    ```cpp
    inline const float getRotation(void) const;
    ```

- *[ getColor ]*:
    - Retorna a cor do jogador.
    - **Retorno**: A cor do jogador como um valor DWORD.
    ```cpp
    inline const DWORD getColor(void) const;
    ```

- *[ getFightingStyle ]*:
    - Retorna o estilo de luta do jogador.
    - **Retorno**: O estilo de luta do jogador como um valor BYTE.
    ```cpp
    inline const BYTE getFightingStyle(void) const;
    ```

- *[ getCheckpointActive ]*:
    - Verifica se o jogador tem um checkpoint ativo.
    - **Retorno**: `true` se o jogador tem um checkpoint ativo, `false` caso contrário.
    ```cpp
    inline const bool getCheckpointActive(void) const;
    ```

- *[ getCheckpointPos ]*:
    - Retorna a posição do checkpoint do jogador.
    - `x`: Referência para a coordenada x da posição do checkpoint.
    - `y`: Referência para a coordenada y da posição do checkpoint.
    - `z`: Referência para a coordenada z da posição do checkpoint.
    ```cpp
    inline void getCheckpointPos(float &x, float &y, float &z) const;
    ```

- *[ getCheckpointSize ]*:
    - Retorna o tamanho do checkpoint do jogador.
    - **Retorno**: O tamanho do checkpoint como um float.
    ```cpp
    inline const float getCheckpointSize(void) const;
    ```

- *[ isPlayerInCheckpoint ]*:
    - Verifica se o jogador está em um checkpoint.
    - **Retorno**: `true` se o jogador está em um checkpoint, `false` caso contrário.
    ```cpp
    inline const bool isPlayerInCheckpoint(void) const;
    ```

- *[ setHealth ]*:
    - Define a saúde do jogador.
    - `value`: O valor da saúde a ser definido.
    ```cpp
    void setHealth(const float value);
    ```

- *[ setArmour ]*:
    - Define a armadura do jogador.
    - `value`: O valor da armadura a ser definido.
    ```cpp
    void setArmour(const float value);
    ```

- *[ setSkin ]*:
    - Define a skin do jogador.
    - `skinid`: O ID da skin a ser definida.
    ```cpp
    void setSkin(const int skinid);
    ```

- *[ setSpawn ]*:
    - Define a posição de spawn do jogador.
    - `x`: A coordenada x da posição de spawn.
    - `y`: A coordenada y da posição de spawn.
    - `z`: A coordenada z da posição de spawn.
    ```cpp
    void setSpawn(const float x, const float y, const float z);
    ```

- *[ setPos ]*:
    - Define a posição atual do jogador.
    - `x`: A coordenada x da posição atual.
    - `y`: A coordenada y da posição atual.
    - `z`: A coordenada z da posição atual.
    ```cpp
    void setPos(const float x, const float y, const float z);
    ```

- *[ setRotation ]*:
    - Define a rotação do jogador.
    - `r`: A rotação a ser definida.
    ```cpp
    void setRotation(const float r);
    ```

- *[ setColor ]*:
    - Define a cor do jogador.
    - `color`: A cor a ser definida.
    ```cpp
    void setColor(const int color);
    ```

- *[ clientMessage ]*:
    - Envia uma mensagem para o cliente.
    - `color`: A cor da mensagem.
    - `message`: O texto da mensagem.
    ```cpp
    void clientMessage(const int color, const char *message);
    ```

- *[ getOnFootSyncData ]*:
    - Retorna os dados de sincronização a pé do jogador.
    - **Retorno**: Um ponteiro para a estrutura `ONFOOT_SYNC_DATA` do jogador.
    ```cpp
    inline internal::packet::ONFOOT_SYNC_DATA *getOnFootSyncData();
    ```

- *[ getInCarSyncData ]*:
    - Retorna os dados de sincronização no carro do jogador.
    - **Retorno**: Um ponteiro para a estrutura `INCAR_SYNC_DATA` do jogador.
    ```cpp
    inline internal::packet::INCAR_SYNC_DATA *getInCarSyncData();
    ```

### Vehicle
[ **CVehicle** ]:

Classe que representa um objeto veículo.

#### Construtor
- `CVehicle()`: Construtor padrão da classe `CVehicle`.

#### Métodos Públicos

- *[ getId ]*:
    - Retorna o ID do veículo.
    - **Retorno**: O ID do veículo.
    ```cpp
    inline const int getId(void) const;
    ```

- *[ getModelId ]*:
    - Retorna o ID do modelo do veículo.
    - **Retorno**: O ID do modelo do veículo.
    ```cpp
    inline const int getModelId(void) const;
    ```

- *[ getHealth ]*:
    - Retorna a saúde do veículo.
    - **Retorno**: A saúde do veículo.
    ```cpp
    inline const float getHealth(void) const;
    ```

- *[ setHealth ]*:
    - Define a saúde do veículo.
    - `value`: O valor da saúde a ser definido.
    ```cpp
    void setHealth(const float value);
    ```

- *[ getPosition ]*:
    - Retorna a posição do veículo.
    - `x`: Referência para a coordenada x.
    - `y`: Referência para a coordenada y.
    - `z`: Referência para a coordenada z.
    ```cpp
    inline void getPosition(float &x, float &y, float &z) const;
    ```

- *[ setPosition ]*:
    - Define a posição do veículo.
    - `x`: A coordenada x.
    - `y`: A coordenada y.
    - `z`: A coordenada z.
    ```cpp
    void setPosition(const float x, const float y, const float z);
    ```

- *[ getRotation ]*:
    - Retorna a rotação do veículo.
    - **Retorno**: A rotação do veículo.
    ```cpp
    inline const float getRotation(void) const;
    ```

- *[ respawn ]*:
    - Respawna o veículo.
    ```cpp
    void respawn(void);
    ```

- *[ Create ]*:
    - Cria um novo veículo.
    - `model`: O ID do modelo do veículo.
    - `x`: A coordenada x da posição inicial.
    - `y`: A coordenada y da posição inicial.
    - `z`: A coordenada z da posição inicial.
    - `rotation`: A rotação inicial do veículo.
    - `color1`: A cor primária do veículo.
    - `color2`: A cor secundária do veículo.
    - `respawndelay`: O tempo de delay para respawn.
    - `respawn`: Indica se o veículo deve respawnar.
    - `siren`: Indica se o veículo possui sirene.
    - `interior`: O ID do interior do veículo.
    - **Retorno**: O ID do veículo criado.
    ```cpp
    static int Create(const uint16_t model, const float x, const float y, const float z, const float rotation,
                      const int color1, const int color2, const int respawndelay, const bool respawn, const bool siren, const int interior);
    ```

- *[ Destroy ]*:
    - Destroi um veículo.
    - `vehicle`: Referência para o veículo a ser destruído.
    - **Retorno**: O ID do veículo destruído.
    ```cpp
    static int Destroy(const CVehicle &vehicle);
    ```