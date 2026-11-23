
#ifndef CONSTRUCOES_H
#define CONSTRUCOES_H

#include "Cidade.h"

class Construcoes {
private:
    static constexpr int PRECO_SOLDADO = 5;
    static constexpr int SERVOS_POR_SOLDADO = 1;
    static constexpr int PRECO_CONSTRUCAO = 20;

public:
    bool recrutarSoldados(Cidade& cidade, int quantidade);
    bool construir(Cidade& cidade, int quantidade);
};

#endif
