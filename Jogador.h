
#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador {
private:
    std::string nome;
    std::string titulo;

public:
    Jogador(const std::string& nome);

    std::string getNome() const;
    std::string getTitulo() const;
};

#endif
