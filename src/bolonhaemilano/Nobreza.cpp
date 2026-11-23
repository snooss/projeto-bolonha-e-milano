#include <algorithm>
#include <limits>
#include "Nobreza.h"

const int Nobreza::PRESTIGIO_MINIMO[6] = {0, 400, 550, 700, 850, 1000};

int Nobreza::calcularPrestigio(const Cidade& cidade) const {
    long long total = static_cast<long long>(cidade.getConstrucoes()) * PESO_CONSTRUCAO
        + static_cast<long long>(cidade.getSoldados()) * PESO_SOLDADO
        + static_cast<long long>(cidade.getServos()) * PESO_SERVO
        + cidade.getTerras() / HECTARES_POR_PONTO;
    return static_cast<int>(std::min(total, static_cast<long long>(std::numeric_limits<int>::max())));
}

int Nobreza::prestigioParaProximoTitulo(const Jogador& jogador) const {
    int proximo = jogador.getNivelTitulo() + 1;
    if (proximo >= 6) return -1;
    return PRESTIGIO_MINIMO[proximo];
}

bool Nobreza::verificarPromocao(Cidade& cidade) const {
    Jogador* dono = cidade.getDono();
    if (!dono) return false;
    int necessario = prestigioParaProximoTitulo(*dono);
    if (necessario < 0 || calcularPrestigio(cidade) < necessario) return false;
    return dono->promover();
}
