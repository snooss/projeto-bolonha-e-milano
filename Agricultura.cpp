#include <algorithm>
#include <limits>
#include "Agricultura.h"

int Agricultura::processarColheita(Cidade& cidade) {
    if (cidade.isColheitaFeita()) return -1;
    long long capacidade = static_cast<long long>(cidade.getServos()) * HECTARES_POR_SERVO;
    int hectares = static_cast<int>(std::min(static_cast<long long>(cidade.getTerras()),
        std::min(capacidade, static_cast<long long>(std::numeric_limits<int>::max() / RENDIMENTO_POR_HECTARE))));
    int sementes = hectares / 2;
    if (sementes > cidade.getGraos()) {
        hectares = std::min(hectares, cidade.getGraos() * 2);
        sementes = hectares / 2;
    }
    if (sementes > 0 && !cidade.removerGraos(sementes)) return 0;
    int producao = hectares * RENDIMENTO_POR_HECTARE;
    cidade.adicionarGraos(producao);
    cidade.marcarColheitaFeita();
    return hectares;
}

bool Agricultura::distribuirAlimentos(Cidade& cidade, int percentual) {
    if (percentual < PERCENTUAL_MINIMO || percentual > PERCENTUAL_MAXIMO) return false;
    int disponiveis = cidade.getGraos();
    int distribuido = static_cast<int>(static_cast<long long>(disponiveis) * percentual / 100);
    if (distribuido > 0 && !cidade.removerGraos(distribuido)) return false;
    int necessidade = cidade.getServos() / SERVOS_POR_GRAO;
    if (distribuido >= necessidade) {
        int crescimento = static_cast<int>(static_cast<long long>(cidade.getServos()) * CRESCIMENTO_PERCENTUAL / 100);
        cidade.adicionarServos(crescimento);
    } else {
        int deficit = necessidade - distribuido;
        cidade.removerServos(std::min(deficit, cidade.getServos()));
    }
    return true;
}
