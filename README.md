# Bolonha e Milano

Jogo de estratégia econômica medieval desenvolvido em **C++17** para o projeto do 4º bimestre.

## Requisitos

- Compilador C++ com suporte a C++17 (GCC/G++).
- Terminal aberto na pasta raiz do projeto.
- No Windows, com MSYS2/MinGW instalado e `g++` disponível no PATH.

## Estrutura

```text
projeto-bolonha-e-milano/
├── README.md
├── src/
│   └── bolonhaemilano/
│       ├── main.cpp
│       ├── Testes.cpp
│       ├── Menu.h / Menu.cpp
│       ├── Cidade.h / Cidade.cpp
│       ├── Jogador.h / Jogador.cpp
│       ├── Partida.h / Partida.cpp
│       ├── Mercado.h / Mercado.cpp
│       ├── Agricultura.h / Agricultura.cpp
│       ├── Governo.h / Governo.cpp
│       ├── Construcoes.h / Construcoes.cpp
│       └── Nobreza.h / Nobreza.cpp
├── uml/
│   ├── diagrama-classes.puml
│   └── diagrama-sequencia-fim-do-ano.puml
└── casos-de-uso/
    └── diagrama-casos-de-uso.puml
```

## Como compilar o jogo

Na raiz do projeto, execute:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Isrc/bolonhaemilano src/bolonhaemilano/main.cpp src/bolonhaemilano/Cidade.cpp src/bolonhaemilano/Jogador.cpp src/bolonhaemilano/Mercado.cpp src/bolonhaemilano/Agricultura.cpp src/bolonhaemilano/Governo.cpp src/bolonhaemilano/Construcoes.cpp src/bolonhaemilano/Nobreza.cpp src/bolonhaemilano/Partida.cpp src/bolonhaemilano/Menu.cpp -o jogo
```

No Windows, pode usar `-o jogo.exe` no lugar de `-o jogo`. Depois execute:

```powershell
.\jogo.exe
```

Em Linux/macOS:

```bash
./jogo
```

## Como jogar

O menu principal apresenta estas opções:

1. **Novo jogo:** inicia uma partida com 1 a 4 jogadores. Cada jogador informa seu nome e escolhe uma cidade disponível.
2. **Ver status da cidade:** mostra ano, governante, título, recursos, impostos, justiça, soldados, construções e ações realizadas no ano.
3. **Mercado:** permite comprar e vender grãos e terras.
4. **Agricultura:** permite realizar a colheita anual e distribuir alimentos.
5. **Governo:** permite arrecadar impostos uma vez por ano, alterar a taxa e definir o nível de justiça.
6. **Construções:** permite recrutar soldados e construir edifícios.
7. **Encerrar turno:** passa a vez ao próximo jogador. Quando o último jogador encerra o turno, o ano avança e as promoções são verificadas.
8. **Ver classificação:** apresenta título e prestígio dos governantes.
9. **Sobre o jogo:** apresenta informações do projeto.
0. **Sair:** encerra o programa.

A partida começa no ano 1400. O primeiro jogador a alcançar o título de Rei/Rainha vence. Caso ninguém alcance esse título, a partida termina após o ano de 1410 e vence o governante com a maior classificação, conforme as regras implementadas.

## Como compilar e executar os testes

A classe `Testes` possui um `main()` próprio e não faz parte do executável do jogo. Para compilar os testes, execute na raiz:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Isrc/bolonhaemilano src/bolonhaemilano/Testes.cpp src/bolonhaemilano/Cidade.cpp src/bolonhaemilano/Jogador.cpp src/bolonhaemilano/Mercado.cpp src/bolonhaemilano/Agricultura.cpp src/bolonhaemilano/Governo.cpp src/bolonhaemilano/Construcoes.cpp src/bolonhaemilano/Nobreza.cpp src/bolonhaemilano/Partida.cpp -o testes
```

No Windows, use `-o testes.exe`. Execute:

```powershell
.\testes.exe
```

Os testes seguem o padrão **preparar, executar e verificar**. Cada verificação imprime `[OK]` ou `[FALHA]`. O resultado esperado desta versão é:

```text
Aprovados: 37 | Reprovados: 0
```

Se algum teste falhar, o programa termina com código de saída 1.

## Diagramas

Os diagramas editáveis em PlantUML estão nas pastas:

- `uml/diagrama-classes.puml`: classes do jogo e classe independente `Testes`.
- `uml/diagrama-sequencia-fim-do-ano.puml`: sequência de chamadas quando o último jogador encerra o turno.
- `casos-de-uso/diagrama-casos-de-uso.puml`: casos de uso do jogador.
