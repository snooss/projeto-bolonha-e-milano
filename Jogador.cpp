#include "Jogador.h"

const std::string Jogador::TITULOS[6] = {
    "Cavaleiro", "Barão", "Conde", "Marquês", "Duque", "Rei/Rainha"
};

Jogador::Jogador(const std::string& nome) : nome(nome), nivelTitulo(0) {}

std::string Jogador::getNome() const { return nome; }
std::string Jogador::getTitulo() const { return TITULOS[nivelTitulo]; }
int Jogador::getNivelTitulo() const { return nivelTitulo; }

bool Jogador::promover() {
    if (ehMonarca()) return false;
    ++nivelTitulo;
    return true;
}

bool Jogador::ehMonarca() const { return nivelTitulo == 5; }
