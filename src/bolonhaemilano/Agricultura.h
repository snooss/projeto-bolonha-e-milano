#ifndef AGRICULTURA_H
#define AGRICULTURA_H

#include "Cidade.h"

class Agricultura {
private:
    static constexpr int HECTARES_POR_SERVO = 5;
    static constexpr int RENDIMENTO_POR_HECTARE = 2;
    static constexpr int SERVOS_POR_GRAO = 5;
    static constexpr int CRESCIMENTO_PERCENTUAL = 5;
    static constexpr int PERCENTUAL_MINIMO = 20;
    static constexpr int PERCENTUAL_MAXIMO = 80;

public:
    int processarColheita(Cidade& cidade);
    bool distribuirAlimentos(Cidade& cidade, int percentual);
};

#endif