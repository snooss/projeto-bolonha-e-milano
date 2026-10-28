
#include <algorithm>
#include <limits>
#include "Agricultura.h"

int Agricultura::processarColheita(Cidade& cidade) {
    // Calcula a capacidade de cultivo.
    long long capacidade =
        static_cast<long long>(cidade.getServos()) *
        HECTARES_POR_SERVO;

    int hectares = static_cast<int>(
        std::min(
            static_cast<long long>(cidade.getTerras()),
            std::min(
                capacidade,
                static_cast<long long>(
                    std::numeric_limits<int>::max() /
                    RENDIMENTO_POR_HECTARE
                )
            )
        )
    );

    // Cada dois hectares precisam de uma unidade de grao
    // como semente, conforme a formula inteira hectares / 2.
    int sementes = hectares / 2;

    // Se faltar semente, reduz a area cultivada.
    if (sementes > cidade.getGraos()) {
        hectares = std::min(
            hectares,
            cidade.getGraos() * 2
        );
        sementes = hectares / 2;
    }

    // Consome as sementes.
    if (sementes > 0 &&
        !cidade.removerGraos(sementes)) {
        return 0;
    }

    // Calcula e adiciona a nova producao.
    int producao = hectares * RENDIMENTO_POR_HECTARE;
    cidade.adicionarGraos(producao);

    return hectares;
}

bool Agricultura::distribuirAlimentos(
    Cidade& cidade, int percentual
) {
    // Valida o percentual de distribuicao.
    if (percentual < PERCENTUAL_MINIMO ||
        percentual > PERCENTUAL_MAXIMO) {
        return false;
    }

    // Calcula a quantidade de graos a distribuir.
    int graosDisponiveis = cidade.getGraos();
    int alimentoDistribuido = static_cast<int>(
        static_cast<long long>(graosDisponiveis) *
        percentual / 100
    );

    // Consome os graos usados na alimentacao.
    if (alimentoDistribuido > 0 &&
        !cidade.removerGraos(alimentoDistribuido)) {
        return false;
    }

    // Calcula a necessidade minima da populacao.
    int necessidade = cidade.getServos() / SERVOS_POR_GRAO;

    if (alimentoDistribuido >= necessidade) {
        // Alimentacao suficiente: crescimento de 5%.
        int crescimento = static_cast<int>(
            static_cast<long long>(cidade.getServos()) *
            CRESCIMENTO_PERCENTUAL / 100
        );

        cidade.adicionarServos(crescimento);
    } else {
        // Alimentacao insuficiente: perde habitantes
        // de acordo com o deficit, sem ficar negativo.
        int deficit = necessidade - alimentoDistribuido;

        cidade.removerServos(
            std::min(deficit, cidade.getServos())
        );
    }

    return true;
}
