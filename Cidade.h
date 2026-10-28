
#ifndef CIDADE_H
#define CIDADE_H

#include <string>
#include "Jogador.h"

class Cidade {
private:
    std::string nome;
    int anoAtual;
    Jogador* dono;

    int florins;
    int terras;
    int graos;
    int servos;

public:
    Cidade(const std::string& nome, Jogador* dono);

    std::string getNome() const;
    int getAnoAtual() const;
    Jogador* getDono() const;

    int getFlorins() const;
    int getTerras() const;
    int getGraos() const;
    int getServos() const;

    void avancarAno();

    void adicionarFlorins(int quantidade);
    bool removerFlorins(int quantidade);

    void adicionarTerras(int quantidade);
    bool removerTerras(int quantidade);

    void adicionarGraos(int quantidade);
    bool removerGraos(int quantidade);

    void exibirStatus() const;

    void adicionarServos(int quantidade);
    bool removerServos(int quantidade);
};

#endif
