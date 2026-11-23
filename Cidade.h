
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

    int taxaImposto;
    std::string nivelJustica;

    int soldados;
    int construcoes;

public:
    Cidade(const std::string& nome, Jogador* dono);

    std::string getNome() const;
    int getAnoAtual() const;
    Jogador* getDono() const;

    int getFlorins() const;
    int getTerras() const;
    int getGraos() const;
    int getServos() const;

    int getTaxaImposto() const;
    void setTaxaImposto(int taxa);

    std::string getNivelJustica() const;
    void setNivelJustica(const std::string& nivel);

    int getSoldados() const;
    int getConstrucoes() const;

    void avancarAno();

    void adicionarFlorins(int quantidade);
    bool removerFlorins(int quantidade);

    void adicionarTerras(int quantidade);
    bool removerTerras(int quantidade);

    void adicionarGraos(int quantidade);
    bool removerGraos(int quantidade);

    void adicionarServos(int quantidade);
    bool removerServos(int quantidade);

    void adicionarSoldados(int quantidade);
    bool removerSoldados(int quantidade);

    void adicionarConstrucoes(int quantidade);
    bool removerConstrucoes(int quantidade);

    void exibirStatus() const;
};

#endif
