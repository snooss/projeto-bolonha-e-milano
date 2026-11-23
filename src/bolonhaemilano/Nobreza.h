#ifndef NOBREZA_H
#define NOBREZA_H

#include "Cidade.h"

class Nobreza {
private:
    static constexpr int PESO_CONSTRUCAO = 10;
    static constexpr int PESO_SOLDADO = 2;
    static constexpr int PESO_SERVO = 1;
    static constexpr int HECTARES_POR_PONTO = 100;
    static const int PRESTIGIO_MINIMO[6];

public:
    int calcularPrestigio(const Cidade& cidade) const;
    int prestigioParaProximoTitulo(const Jogador& jogador) const;
    bool verificarPromocao(Cidade& cidade) const;
};

#endif
