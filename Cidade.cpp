
#include <iostream>
#include "Cidade.h"

Cidade::Cidade(const std::string& nome, Jogador* dono) {
    this->nome = nome;
    this->dono = dono;
    this->anoAtual = 1400;
}

void Cidade::avancarAno() {
    anoAtual++;
}

void Cidade::exibirStatus() const {
    std::cout << "\n========== STATUS DA CIDADE ==========\n";
    std::cout << "Cidade: " << nome << '\n';
    std::cout << "Governante: " << dono->getNome() << '\n';
    std::cout << "Titulo: " << dono->getTitulo() << '\n';
    std::cout << "Ano atual: " << anoAtual << '\n';
    std::cout << "======================================\n";
}
