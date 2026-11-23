#include <cstdlib>
#include <iostream>
#include <string>

#include "Cidade.h"
#include "Mercado.h"
#include "Agricultura.h"
#include "Governo.h"
#include "Construcoes.h"
#include "Jogador.h"
#include "Nobreza.h"
#include "Partida.h"

class Testes {
private:
    static int aprovados;
    static int reprovados;

    static void verificar(const std::string& descricao, bool condicao) {
        if (condicao) {
            ++aprovados;
            std::cout << "[OK]    " << descricao << '\n';
        } else {
            ++reprovados;
            std::cout << "[FALHA] " << descricao << '\n';
        }
    }

    static Cidade novaCidade() {
        static Jogador dono("Teste");
        return Cidade("Bolonha", &dono);
    }

    static void testarCidade() {
        std::cout << "\n-- Cidade --\n";
        Cidade cidade = novaCidade();
        verificar("cidade inicia com 1000 florins", cidade.getFlorins() == 1000);
        verificar("cidade inicia no ano 1400", cidade.getAnoAtual() == 1400);
        verificar("remover florins acima do saldo e recusado", !cidade.removerFlorins(1001));
        verificar("saldo nao muda apos remocao recusada", cidade.getFlorins() == 1000);
        cidade.marcarColheitaFeita();
        cidade.avancarAno();
        verificar("avancarAno soma um ao ano", cidade.getAnoAtual() == 1401);
        verificar("avancarAno libera colheita novamente", !cidade.isColheitaFeita());
    }

    static void testarMercado() {
        std::cout << "\n-- Mercado --\n";
        Mercado mercado;
        Cidade cidade = novaCidade();
        verificar("comprar 100 graos funciona", mercado.comprarGraos(cidade, 100));
        verificar("compra de graos custa 200 florins", cidade.getFlorins() == 800);
        verificar("compra adiciona 100 graos", cidade.getGraos() == 600);
        verificar("quantidade negativa e recusada", !mercado.comprarGraos(cidade, -10));
        Cidade semSaldo = novaCidade();
        semSaldo.removerFlorins(950);
        verificar("compra sem florins suficientes e recusada", !mercado.comprarGraos(semSaldo, 100));
    }

    static void testarAgricultura() {
        std::cout << "\n-- Agricultura --\n";
        Agricultura agricultura;
        Cidade cidade = novaCidade();
        verificar("primeira colheita cultiva 1000 hectares", agricultura.processarColheita(cidade) == 1000);
        verificar("colheita deixa 2000 graos", cidade.getGraos() == 2000);
        verificar("segunda colheita no mesmo ano e recusada", agricultura.processarColheita(cidade) == -1);
        verificar("distribuir 10 por cento e recusado", !agricultura.distribuirAlimentos(cidade, 10));
    }

    static void testarGoverno() {
        std::cout << "\n-- Governo --\n";
        Governo governo;
        Cidade cidade = novaCidade();
        verificar("taxa de 60 por cento e recusada", !governo.definirTaxaImposto(cidade, 60));
        verificar("justica Branda e recusada", !governo.definirJustica(cidade, "Branda"));
        cidade.setNivelJustica("Severa");
        verificar("200 servos, 10 por cento, Severa arrecada 26", governo.arrecadarImpostos(cidade) == 26);
        verificar("segunda arrecadacao no ano e recusada", governo.arrecadarImpostos(cidade) == -1);
    }

    static void testarConstrucoes() {
        std::cout << "\n-- Construcoes --\n";
        Construcoes construcoes;
        Cidade cidade = novaCidade();
        cidade.removerServos(150);
        verificar("recrutar 100 soldados com apenas 50 servos e recusado",
                  !construcoes.recrutarSoldados(cidade, 100));
        verificar("recrutamento recusado nao debita florins", cidade.getFlorins() == 1000);
        Cidade cidadeObras = novaCidade();
        verificar("construir 10 edificios funciona", construcoes.construir(cidadeObras, 10));
        verificar("construir 10 custa 200 florins", cidadeObras.getFlorins() == 800);
    }

    static void testarJogadorENobreza() {
        std::cout << "\n-- Jogador e Nobreza --\n";
        Jogador jogador("Nobre");
        Cidade cidade("Bolonha", &jogador);
        Nobreza nobreza;
        verificar("jogador comeca como Cavaleiro", jogador.getTitulo() == "Cavaleiro");
        verificar("prestigio inicial e 300", nobreza.calcularPrestigio(cidade) == 300);
        verificar("prestigio 300 nao promove", !nobreza.verificarPromocao(cidade));
        cidade.adicionarConstrucoes(50);
        verificar("50 construcoes promovem a Barao", nobreza.verificarPromocao(cidade) &&
                  jogador.getTitulo() == "Barão");
        verificar("promocao sobe apenas um titulo por chamada", jogador.getNivelTitulo() == 1);
        for (int i = 0; i < 4; ++i) jogador.promover();
        verificar("nao e possivel promover alem de Rei/Rainha", !jogador.promover() && jogador.ehMonarca());
    }

    static void testarPartida() {
        std::cout << "\n-- Partida --\n";
        Partida partida;
        Nobreza nobreza;
        bool adicionouJogadores = partida.adicionarCidade("Ana", "Bolonha") &&
                                 partida.adicionarCidade("Bia", "Milano");
        verificar("adiciona dois jogadores e cidades", adicionouJogadores);
        verificar("primeiro turno pertence a Bolonha", partida.getCidadeAtual()->getNome() == "Bolonha");
        verificar("primeiro passarTurno nao fecha o ano", !partida.passarTurno());
        verificar("agora e a vez de Milano", partida.getCidadeAtual()->getNome() == "Milano");
        verificar("turno do ultimo jogador fecha a rodada", partida.passarTurno());
        partida.encerrarAno(nobreza);
        verificar("encerrarAno avanca todas as cidades", partida.getCidades()[0]->getAnoAtual() == 1401 &&
                  partida.getCidades()[1]->getAnoAtual() == 1401);
        verificar("partida nao termina em 1401", !partida.terminou());
        verificar("quinta cidade e recusada (maximo quatro)", [&partida]() {
            partida.adicionarCidade("Caio", "Florença");
            partida.adicionarCidade("Duda", "Veneza");
            return !partida.adicionarCidade("Eva", "Roma");
        }());
    }

public:
    static int main() {
        aprovados = 0;
        reprovados = 0;
        std::cout << "===== TESTES BOLONHA E MILANO =====\n";
        testarCidade();
        testarMercado();
        testarAgricultura();
        testarGoverno();
        testarConstrucoes();
        testarJogadorENobreza();
        testarPartida();
        std::cout << "\nAprovados: " << aprovados << " | Reprovados: " << reprovados << '\n';
        if (reprovados > 0) {
            std::exit(1);
        }
        return 0;
    }
};

int Testes::aprovados = 0;
int Testes::reprovados = 0;

int main() {
    return Testes::main();
}
