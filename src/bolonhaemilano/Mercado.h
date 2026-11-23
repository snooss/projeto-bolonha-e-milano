
#ifndef MERCADO_H
#define MERCADO_H

#include "Cidade.h"

class Mercado {
private:
    static constexpr int PRECO_GRAO = 2;
    static constexpr int PRECO_TERRA = 10;

public:
    int getPrecoGrao() const;
    int getPrecoTerra() const;

    bool comprarGraos(Cidade& cidade, int quantidade);
    bool venderGraos(Cidade& cidade, int quantidade);

    bool comprarTerras(Cidade& cidade, int quantidade);
    bool venderTerras(Cidade& cidade, int quantidade);
};

#endif
