
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
    this->servos = 200;

    this->taxaImposto = 10;
    this->nivelJustica = "Moderada";

    this->soldados = 0;
    this->construcoes = 0;
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

int Cidade::getServos() const {
    return servos;
}

int Cidade::getTaxaImposto() const {
    return taxaImposto;
}

void Cidade::setTaxaImposto(int taxa) {
    taxaImposto = taxa;
}

std::string Cidade::getNivelJustica() const {
    return nivelJustica;
}

void Cidade::setNivelJustica(const std::string& nivel) {
    nivelJustica = nivel;
}

int Cidade::getSoldados() const {
    return soldados;
}

int Cidade::getConstrucoes() const {
    return construcoes;
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

void Cidade::adicionarServos(int quantidade) {
    if (quantidade > 0 &&
        quantidade <= std::numeric_limits<int>::max() - servos) {
        servos += quantidade;
    }
}

bool Cidade::removerServos(int quantidade) {
    if (quantidade <= 0 || quantidade > servos) {
        return false;
    }

    servos -= quantidade;
    return true;
}

void Cidade::adicionarSoldados(int quantidade) {
    if (quantidade > 0 &&
        quantidade <= std::numeric_limits<int>::max() - soldados) {
        soldados += quantidade;
    }
}

bool Cidade::removerSoldados(int quantidade) {
    if (quantidade <= 0 || quantidade > soldados) {
        return false;
    }

    soldados -= quantidade;
    return true;
}

void Cidade::adicionarConstrucoes(int quantidade) {
    if (quantidade > 0 &&
        quantidade <= std::numeric_limits<int>::max() - construcoes) {
        construcoes += quantidade;
    }
}

bool Cidade::removerConstrucoes(int quantidade) {
    if (quantidade <= 0 || quantidade > construcoes) {
        return false;
    }

    construcoes -= quantidade;
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
    std::cout << "Servos: " << servos << '\n';

    std::cout << "Taxa de imposto: " << taxaImposto << "%\n";
    std::cout << "Nivel de justica: " << nivelJustica << '\n';

    std::cout << "Soldados: " << soldados << '\n';
    std::cout << "Construcoes: " << construcoes << '\n';

    std::cout << "======================================\n";
}
