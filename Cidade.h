
#ifndef CIDADE_H
#define CIDADE_H

#include <string>
#include "Jogador.h"

class Cidade {
private:
    std::string nome;
    int anoAtual;
    Jogador* dono;

public:
    Cidade(const std::string& nome, Jogador* dono);

    void avancarAno();
    void exibirStatus() const;
};

#endif
