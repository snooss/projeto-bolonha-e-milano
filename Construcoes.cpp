
#include <limits>
#include "Construcoes.h"

bool Construcoes::recrutarSoldados(
    Cidade& cidade,
    int quantidade
) {
    if (quantidade <= 0) {
        return false;
    }

    if (quantidade >
        std::numeric_limits<int>::max() / PRECO_SOLDADO) {
        return false;
    }

    int custo = quantidade * PRECO_SOLDADO;
    int servosNecessarios = quantidade * SERVOS_POR_SOLDADO;

    if (cidade.getFlorins() < custo ||
        cidade.getServos() < servosNecessarios) {
        return false;
    }

    if (quantidade >
        std::numeric_limits<int>::max() - cidade.getSoldados()) {
        return false;
    }

    cidade.removerFlorins(custo);
    cidade.removerServos(servosNecessarios);
    cidade.adicionarSoldados(quantidade);

    return true;
}

bool Construcoes::construir(
    Cidade& cidade,
    int quantidade
) {
    if (quantidade <= 0) {
        return false;
    }

    if (quantidade >
        std::numeric_limits<int>::max() / PRECO_CONSTRUCAO) {
        return false;
    }

    int custo = quantidade * PRECO_CONSTRUCAO;

    if (quantidade >
        std::numeric_limits<int>::max() - cidade.getConstrucoes()) {
        return false;
    }

    if (!cidade.removerFlorins(custo)) {
        return false;
    }

    cidade.adicionarConstrucoes(quantidade);

    return true;
}
