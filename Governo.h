#ifndef GOVERNO_H
#define GOVERNO_H

#include <string>
#include "Cidade.h"

class Governo {
private:
    static constexpr int TAXA_MAXIMA = 50;

    static constexpr double MULTIPLICADOR_JUSTA = 0.8;
    static constexpr double MULTIPLICADOR_MODERADA = 1.0;
    static constexpr double MULTIPLICADOR_SEVERA = 1.3;

    double multiplicadorPara(const std::string& nivel) const;

public:
    int arrecadarImpostos(Cidade& cidade);

    bool definirTaxaImposto(Cidade& cidade, int taxa);

    bool definirJustica(
        Cidade& cidade,
        const std::string& nivel
    );
};

#endif