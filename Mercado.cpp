
#include <limits>
#include "Mercado.h"

int Mercado::getPrecoGrao() const {
    return PRECO_GRAO;
}

int Mercado::getPrecoTerra() const {
    return PRECO_TERRA;
}

bool Mercado::comprarGraos(Cidade& cidade, int quantidade) {
    if (quantidade <= 0) {
        return false;
    }

    long long custo =
        static_cast<long long>(quantidade) * PRECO_GRAO;

    if (custo > std::numeric_limits<int>::max()) {
        return false;
    }

    if (quantidade >
        std::numeric_limits<int>::max() - cidade.getGraos()) {
        return false;
    }

    if (!cidade.removerFlorins(static_cast<int>(custo))) {
        return false;
    }

    cidade.adicionarGraos(quantidade);
    return true;
}

bool Mercado::venderGraos(Cidade& cidade, int quantidade) {
    if (quantidade <= 0) {
        return false;
    }

    long long receita =
        static_cast<long long>(quantidade) * PRECO_GRAO;

    if (receita > std::numeric_limits<int>::max()) {
        return false;
    }

    if (receita >
        std::numeric_limits<int>::max() - cidade.getFlorins()) {
        return false;
    }

    if (!cidade.removerGraos(quantidade)) {
        return false;
    }

    cidade.adicionarFlorins(static_cast<int>(receita));
    return true;
}

bool Mercado::comprarTerras(Cidade& cidade, int quantidade) {
    if (quantidade <= 0) {
        return false;
    }

    long long custo =
        static_cast<long long>(quantidade) * PRECO_TERRA;

    if (custo > std::numeric_limits<int>::max()) {
        return false;
    }

    if (quantidade >
        std::numeric_limits<int>::max() - cidade.getTerras()) {
        return false;
    }

    if (!cidade.removerFlorins(static_cast<int>(custo))) {
        return false;
    }

    cidade.adicionarTerras(quantidade);
    return true;
}

bool Mercado::venderTerras(Cidade& cidade, int quantidade) {
    if (quantidade <= 0) {
        return false;
    }

    long long receita =
        static_cast<long long>(quantidade) * PRECO_TERRA;

    if (receita > std::numeric_limits<int>::max()) {
        return false;
    }

    if (receita >
        std::numeric_limits<int>::max() - cidade.getFlorins()) {
        return false;
    }

    if (!cidade.removerTerras(quantidade)) {
        return false;
    }

    cidade.adicionarFlorins(static_cast<int>(receita));
    return true;
}
