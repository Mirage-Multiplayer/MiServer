# MiServer NetGame API

### NetGame

#### Funções para Jogador

- *[ getPlayer ]*:
    - Obtém o jogador especificado pelo ID.
    - `game`: O objeto do jogo.
    - `playerid`: O ID do jogador.
    - **Retorno**: Um objeto `mimp_netgame_player_t` representando o jogador.
    ```c
    mimp_netgame_player_t mimp_netgame__getPlayer(mimp_netgame_t game, int playerid);
    ```

- *[ getId ]*:
    - Retorna o ID do jogador.
    - **Retorno**: O ID do jogador.
    ```c
    int mimp_netgame_player__getId(mimp_netgame_player_t);
    ```

- *[ getNickName ]*:
    - Obtém o apelido do jogador.
    - `nickname`: Buffer para armazenar o apelido.
    ```c
    void mimp_netgame_player__getNickName(mimp_netgame_player_t, char *nickname);
    ```

- *[ getIP ]*:
    - Obtém o endereço IP do jogador.
    - `ip`: Buffer para armazenar o IP do jogador.
    ```c
    void mimp_netgame_player__getIP(mimp_netgame_player_t, char *ip);
    ```

- *[ getPort ]*:
    - Retorna o número da porta do cliente.
    - **Retorno**: O número da porta do cliente.
    ```c
    int mimp_netgame_player__getPort(mimp_netgame_player_t);
    ```

- *[ getScore ]*:
    - Retorna a pontuação do jogador.
    - **Retorno**: A pontuação do jogador.
    ```c
    int mimp_netgame_player__getScore(mimp_netgame_player_t);
    ```

- *[ getPing ]*:
    - Retorna o ping do jogador.
    - **Retorno**: O ping do jogador em milissegundos.
    ```c
    int mimp_netgame_player__getPing(mimp_netgame_player_t);
    ```

- *[ getPos ]*:
    - Obtém a posição atual do jogador.
    - `x`, `y`, `z`: Ponteiros para armazenar as coordenadas da posição.
    ```c
    void mimp_netgame_player__getPos(mimp_netgame_player_t, float *x, float *y, float *z);
    ```

- *[ getRotation ]*:
    - Obtém a rotação atual do jogador.
    - `r`: Ponteiro para armazenar a rotação do jogador.
    ```c
    void mimp_netgame_player__getRotation(mimp_netgame_player_t, float *r);
    ```

- *[ getCurrentVehicle ]*:
    - Retorna o ID do veículo no qual o jogador está atualmente.
    - **Retorno**: O ID do veículo atual.
    ```c
    int mimp_netgame_player__getCurrentVehicle(mimp_netgame_player_t);
    ```

- *[ getSkin ]*:
    - Retorna o ID da skin do jogador.
    - **Retorno**: O ID da skin do jogador.
    ```c
    int mimp_netgame_player__getSkin(mimp_netgame_player_t);
    ```

- *[ getSpawn ]*:
    - Obtém a posição de spawn do jogador.
    - `x`, `y`, `z`: Ponteiros para armazenar as coordenadas de spawn.
    ```c
    void mimp_netgame_player__getSpawn(mimp_netgame_player_t, float *x, float *y, float *z);
    ```

- *[ getInteriorId ]*:
    - Retorna o ID do interior em que o jogador está.
    - **Retorno**: O ID do interior.
    ```c
    int mimp_netgame_player__getInteriorId(mimp_netgame_player_t);
    ```

- *[ getCheckpointPos ]*:
    - Obtém a posição do checkpoint do jogador.
    - `x`, `y`, `z`: Ponteiros para armazenar as coordenadas do checkpoint.
    ```c
    void mimp_netgame_player__getCheckpointPos(mimp_netgame_player_t, float *x, float *y, float *z);
    ```

- *[ getCheckpointSize ]*:
    - Retorna o tamanho do checkpoint do jogador.
    - **Retorno**: O tamanho do checkpoint.
    ```c
    float mimp_netgame_player__getCheckpointSize(mimp_netgame_player_t);
    ```

- *[ getFightingStyle ]*:
    - Retorna o estilo de luta do jogador.
    - **Retorno**: O estilo de luta do jogador.
    ```c
    int mimp_netgame_player__getFightingStyle(mimp_netgame_player_t);
    ```

- *[ getHealth ]*:
    - Obtém a saúde do jogador.
    - `d`: Ponteiro para armazenar o valor da saúde.
    - **Retorno**: 0 em caso de sucesso, -1 em caso de erro.
    ```c
    int mimp_netgame_player__getHealth(mimp_netgame_player_t, float *d);
    ```

- *[ getArmour ]*:
    - Obtém o valor da armadura do jogador.
    - `d`: Ponteiro para armazenar o valor da armadura.
    - **Retorno**: 0 em caso de sucesso, -1 em caso de erro.
    ```c
    int mimp_netgame_player__getArmour(mimp_netgame_player_t, float *d);
    ```

- *[ setHealth ]*:
    - Define a saúde do jogador.
    - `value`: O valor da saúde.
    ```c
    void mimp_netgame_player__setHealth(mimp_netgame_player_t, float value);
    ```

- *[ setArmour ]*:
    - Define o valor da armadura do jogador.
    - `value`: O valor da armadura.
    ```c
    void mimp_netgame_player__setArmour(mimp_netgame_player_t, float value);
    ```

- *[ setSkin ]*:
    - Define a skin do jogador.
    - `skinid`: O ID da skin.
    ```c
    void mimp_netgame_player__setSkin(mimp_netgame_player_t, int skinid);
    ```

- *[ setSpawn ]*:
    - Define a posição de spawn do jogador.
    - `x`, `y`, `z`: Coordenadas para definir o local de spawn.
    ```c
    void mimp_netgame_player__setSpawn(mimp_netgame_player_t, float x, float y, float z);
    ```

- *[ setPos ]*:
    - Define a posição atual do jogador.
    - `x`, `y`, `z`: Coordenadas para definir a posição.
    ```c
    void mimp_netgame_player__setPos(mimp_netgame_player_t, float x, float y, float z);
    ```

- *[ setRotation ]*:
    - Define a rotação do jogador.
    - `r`: O valor da rotação.
    ```c
    void mimp_netgame_player__setRotation(mimp_netgame_player_t, float r);
    ```

- *[ setColor ]*:
    - Define a cor do jogador.
    - `color`: O valor da cor.
    ```c
    void mimp_netgame_player__setColor(mimp_netgame_player_t, int color);
    ```

- *[ clientMessage ]*:
    - Envia uma mensagem para o jogador.
    - `color`: A cor da mensagem.
    - `message`: O conteúdo da mensagem.
    ```c
    void mimp_netgame_player__clientMessage(mimp_netgame_player_t, int color, const char *message);
    ```

- *[ setCheckpoint ]*:
    - Define um checkpoint para o jogador.
    - `x`, `y`, `z`: Coordenadas do checkpoint.
    - `size`: Tamanho do checkpoint.
    ```c
    void mimp_netgame_player__setCheckpoint(mimp_netgame_player_t, float x, float y, float z, float size);
    ```

- *[ disableCheckpoint ]*:
    - Desativa o checkpoint ativo do jogador.
    ```c
    void mimp_netgame_player__disableCheckpoint(mimp_netgame_player_t);
    ```

- *[ inCheckpoint ]*:
    - Verifica se o jogador está em um checkpoint.
    - **Retorno**: `1` se o jogador estiver em um checkpoint, `0` caso contrário.
    ```c
    int mimp_netgame_player__inCheckpoint(mimp_netgame_player_t);
    ```