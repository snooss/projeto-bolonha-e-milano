#include <algorithm>
#include <limits>
#include "Governo.h"

double Governo::multiplicadorPara(const std::string& nivel) const {
    if (nivel == "Justa") return MULTIPLICADOR_JUSTA;
    if (nivel == "Moderada") return MULTIPLICADOR_MODERADA;
    if (nivel == "Severa") return MULTIPLICADOR_SEVERA;
    return 0.0;
}

int Governo::arrecadarImpostos(Cidade& cidade) {
    if (cidade.isImpostosArrecadados()) return -1;
    long long base = static_cast<long long>(cidade.getServos()) * cidade.getTaxaImposto() / 100;
    long double valor = static_cast<long double>(base) * multiplicadorPara(cidade.getNivelJustica());
    int limite = std::numeric_limits<int>::max() - cidade.getFlorins();
    int arrecadado = static_cast<int>(std::min(valor, static_cast<long double>(limite)));
    if (arrecadado > 0) cidade.adicionarFlorins(arrecadado);
    cidade.marcarImpostosArrecadados();
    return arrecadado;
}

bool Governo::definirTaxaImposto(Cidade& cidade, int taxa) {
    if (taxa < 0 || taxa > TAXA_MAXIMA) return false;
    cidade.setTaxaImposto(taxa); return true;
}

bool Governo::definirJustica(Cidade& cidade, const std::string& nivel) {
    if (nivel != "Justa" && nivel != "Moderada" && nivel != "Severa") return false;
    cidade.setNivelJustica(nivel); return true;
}
