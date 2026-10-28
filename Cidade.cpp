
#include <iostream>
#include <limits>
#include "Cidade.h"

Cidade::Cidade(const std::string& nome, Jogador* dono) {
    this->nome = nome;
    this->dono = dono;
    this->anoAtual = 1400;

    this->florins = 1000;
    this->terras = 10000;
    this->graos = 500;
}

std::string Cidade::getNome() const {
    return nome;
}

int Cidade::getAnoAtual() const {
    return anoAtual;
}

Jogador* Cidade::getDono() const {
    return dono;
}

int Cidade::getFlorins() const {
    return florins;
}

int Cidade::getTerras() const {
    return terras;
}

int Cidade::getGraos() const {
    return graos;
}

void Cidade::avancarAno() {
    if (anoAtual < std::numeric_limits<int>::max()) {
        anoAtual++;
    }
}

void Cidade::adicionarFlorins(int quantidade) {
    if (quantidade > 0 &&
        quantidade <= std::numeric_limits<int>::max() - florins) {
        florins += quantidade;
    }
}

bool Cidade::removerFlorins(int quantidade) {
    if (quantidade <= 0 || quantidade > florins) {
        return false;
    }

    florins -= quantidade;
    return true;
}

void Cidade::adicionarTerras(int quantidade) {
    if (quantidade > 0 &&
        quantidade <= std::numeric_limits<int>::max() - terras) {
        terras += quantidade;
    }
}

bool Cidade::removerTerras(int quantidade) {
    if (quantidade <= 0 || quantidade > terras) {
        return false;
    }

    terras -= quantidade;
    return true;
}

void Cidade::adicionarGraos(int quantidade) {
    if (quantidade > 0 &&
        quantidade <= std::numeric_limits<int>::max() - graos) {
        graos += quantidade;
    }
}

bool Cidade::removerGraos(int quantidade) {
    if (quantidade <= 0 || quantidade > graos) {
        return false;
    }

    graos -= quantidade;
    return true;
}

void Cidade::exibirStatus() const {
    std::cout << "\n========== STATUS DA CIDADE ==========\n";
    std::cout << "Cidade: " << nome << '\n';
    std::cout << "Governante: " << dono->getNome() << '\n';
    std::cout << "Titulo: " << dono->getTitulo() << '\n';
    std::cout << "Ano atual: " << anoAtual << '\n';
    std::cout << "Florins: " << florins << '\n';
    std::cout << "Terras: " << terras << " hectares\n";
    std::cout << "Graos: " << graos << " unidades\n";
    std::cout << "======================================\n";
}
