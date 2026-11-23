#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador {
private:
    static const std::string TITULOS[6];
    std::string nome;
    int nivelTitulo;

public:
    explicit Jogador(const std::string& nome);
    std::string getNome() const;
    std::string getTitulo() const;
    int getNivelTitulo() const;
    bool promover();
    bool ehMonarca() const;
};

#endif
