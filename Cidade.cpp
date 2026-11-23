#include <iostream>
#include <limits>
#include "Cidade.h"

Cidade::Cidade(const std::string& nome, Jogador* dono)
    : nome(nome), anoAtual(1400), dono(dono), florins(1000), terras(10000),
      graos(500), servos(200), taxaImposto(10), nivelJustica("Moderada"),
      soldados(0), construcoes(0), colheitaFeita(false), impostosArrecadados(false) {}

std::string Cidade::getNome() const { return nome; }
int Cidade::getAnoAtual() const { return anoAtual; }
Jogador* Cidade::getDono() const { return dono; }
int Cidade::getFlorins() const { return florins; }
int Cidade::getTerras() const { return terras; }
int Cidade::getGraos() const { return graos; }
int Cidade::getServos() const { return servos; }
int Cidade::getTaxaImposto() const { return taxaImposto; }
void Cidade::setTaxaImposto(int taxa) { taxaImposto = taxa; }
std::string Cidade::getNivelJustica() const { return nivelJustica; }
void Cidade::setNivelJustica(const std::string& nivel) { nivelJustica = nivel; }
int Cidade::getSoldados() const { return soldados; }
int Cidade::getConstrucoes() const { return construcoes; }
bool Cidade::isColheitaFeita() const { return colheitaFeita; }
void Cidade::marcarColheitaFeita() { colheitaFeita = true; }
bool Cidade::isImpostosArrecadados() const { return impostosArrecadados; }
void Cidade::marcarImpostosArrecadados() { impostosArrecadados = true; }

void Cidade::avancarAno() {
    if (anoAtual < std::numeric_limits<int>::max()) ++anoAtual;
    colheitaFeita = false;
    impostosArrecadados = false;
}

#define IMPLEMENTAR_RECURSO(NOME, ATRIBUTO) \
void Cidade::adicionar##NOME(int q) { \
    if (q > 0 && q <= std::numeric_limits<int>::max() - ATRIBUTO) ATRIBUTO += q; \
} \
bool Cidade::remover##NOME(int q) { \
    if (q <= 0 || q > ATRIBUTO) return false; \
    ATRIBUTO -= q; return true; \
}
IMPLEMENTAR_RECURSO(Florins, florins)
IMPLEMENTAR_RECURSO(Terras, terras)
IMPLEMENTAR_RECURSO(Graos, graos)
IMPLEMENTAR_RECURSO(Servos, servos)
IMPLEMENTAR_RECURSO(Soldados, soldados)
IMPLEMENTAR_RECURSO(Construcoes, construcoes)
#undef IMPLEMENTAR_RECURSO

void Cidade::exibirStatus() const {
    std::cout << "\n========== STATUS DA CIDADE ==========\n"
              << "Cidade: " << nome << '\n'
              << "Governante: " << dono->getNome() << '\n'
              << "Titulo: " << dono->getTitulo() << '\n'
              << "Ano atual: " << anoAtual << '\n'
              << "Florins: " << florins << '\n'
              << "Terras: " << terras << " hectares\n"
              << "Graos: " << graos << '\n'
              << "Servos: " << servos << '\n'
              << "Taxa de imposto: " << taxaImposto << "%\n"
              << "Nivel de justica: " << nivelJustica << '\n'
              << "Soldados: " << soldados << '\n'
              << "Construcoes: " << construcoes << '\n'
              << "Colheita neste ano: " << (colheitaFeita ? "sim" : "nao") << '\n'
              << "Impostos neste ano: " << (impostosArrecadados ? "sim" : "nao") << '\n'
              << "======================================\n";
}
