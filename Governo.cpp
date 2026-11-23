#include <algorithm>
#include <limits>
#include "Governo.h"

double Governo::multiplicadorPara(
    const std::string& nivel
) const {
    if (nivel == "Justa") {
        return MULTIPLICADOR_JUSTA;
    }

    if (nivel == "Moderada") {
        return MULTIPLICADOR_MODERADA;
    }

    if (nivel == "Severa") {
        return MULTIPLICADOR_SEVERA;
    }

    return 0.0;
}

int Governo::arrecadarImpostos(Cidade& cidade) {
    // Calcula a base dos impostos com base na populacao.
    long long base =
        static_cast<long long>(cidade.getServos()) *
        cidade.getTaxaImposto() / 100;

    // Obtém o multiplicador correspondente a justica atual.
    double multiplicador =
        multiplicadorPara(cidade.getNivelJustica());

    // Calcula o valor arrecadado.
    long double valor =
        static_cast<long double>(base) * multiplicador;

    // Evita ultrapassar o limite de florins armazenavel.
    int limite = std::numeric_limits<int>::max()
                 - cidade.getFlorins();

    int arrecadado = static_cast<int>(
        std::min(
            valor,
            static_cast<long double>(limite)
        )
    );

    // Adiciona os impostos ao tesouro da cidade.
    if (arrecadado > 0) {
        cidade.adicionarFlorins(arrecadado);
    }

    return arrecadado;
}

bool Governo::definirTaxaImposto(
    Cidade& cidade,
    int taxa
) {
    // A taxa deve estar entre 0 e 50.
    if (taxa < 0 || taxa > TAXA_MAXIMA) {
        return false;
    }

    cidade.setTaxaImposto(taxa);

    return true;
}

bool Governo::definirJustica(
    Cidade& cidade,
    const std::string& nivel
) {
    // Aceita somente os tres niveis previstos.
    if (nivel != "Justa" &&
        nivel != "Moderada" &&
        nivel != "Severa") {
        return false;
    }

    cidade.setNivelJustica(nivel);

    return true;
}