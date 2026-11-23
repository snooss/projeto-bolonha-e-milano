#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "Menu.h"

Menu::Menu() : emExecucao(true), cidade(nullptr) {}

void Menu::executar() {
    while (emExecucao) {
        exibirOpcoes();
        processarOpcao(lerOpcao());
    }
    std::cout << "\nJogo encerrado. Ate nunca mais!\n";
}

void Menu::exibirOpcoes() {
    std::cout << "\n==========================================\n"
              << "             BOLONHA E MILANO\n"
              << " Um jogo de estrategia economica medieval\n"
              << "==========================================\n";
    if (partida) {
        std::cout << "Ano: " << partida->getAnoAtual() << " | Jogador da vez: "
                  << cidade->getDono()->getNome() << " | Cidade: " << cidade->getNome() << "\n";
    }
    std::cout << "1 - Novo jogo\n2 - Ver status da cidade\n3 - Mercado\n"
              << "4 - Agricultura\n5 - Governo\n6 - Construcoes\n"
              << "7 - Encerrar turno\n8 - Ver classificacao\n9 - Sobre o jogo\n0 - Sair\n"
              << "Escolha uma opcao: ";
}

int Menu::lerInteiro() {
    std::string entrada;
    if (!std::getline(std::cin, entrada)) return -1;
    try {
        std::size_t posicao = 0;
        int valor = std::stoi(entrada, &posicao);
        if (entrada.find_first_not_of(" \\t\\r\\n", posicao) != std::string::npos) return -1;
        return valor;
    } catch (const std::exception&) {
        return -1;
    }
}

int Menu::lerOpcao() {
    return lerInteiro();
}

int Menu::lerQuantidade() {
    std::cout << "Digite a quantidade: ";
    return lerInteiro();
}

bool Menu::exigirJogoEmAndamento() {
    if (!partida || !cidade) {
        std::cout << "\nNenhum jogo em andamento. Inicie um novo jogo primeiro.\n";
        return false;
    }
    return true;
}

void Menu::processarOpcao(int opcao) {
    switch (opcao) {
        case 1: iniciarNovoJogo(); break;
        case 2: exibirStatus(); break;
        case 3: abrirMercado(); break;
        case 4: abrirAgricultura(); break;
        case 5: abrirGoverno(); break;
        case 6: abrirConstrucoes(); break;
        case 7: encerrarTurno(); break;
        case 8: exibirClassificacao(); break;
        case 9: exibirSobre(); break;
        case 0: emExecucao = false; break;
        default: std::cout << "\nOpcao invalida!\n"; break;
    }
}

void Menu::iniciarNovoJogo() {
    int quantidade;
    std::cout << "\nQuantos jogadores participarao? (1 a 4; padrao 2): ";
    quantidade = lerOpcao();
    if (quantidade < 1 || quantidade > 4) {
        quantidade = 2;
        std::cout << "Quantidade invalida. O jogo sera iniciado com 2 jogadores.\n";
    }

    const std::string cidadesDisponiveis[4] = {"Bolonha", "Milano", "Florença", "Veneza"};
    bool cidadeOcupada[4] = {false, false, false, false};
    partida = std::make_unique<Partida>();
    for (int i = 0; i < quantidade; ++i) {
        std::string nome;
        std::cout << "\nNome do jogador " << (i + 1) << ": ";
        std::getline(std::cin, nome);
        if (nome.find_first_not_of(" \t\r\n") == std::string::npos)
            nome = "Jogador " + std::to_string(i + 1);

        int escolhaCidade = -1;
        while (escolhaCidade < 1 || escolhaCidade > 4 || cidadeOcupada[escolhaCidade - 1]) {
            std::cout << "Escolha a cidade de " << nome << ":\n";
            for (int j = 0; j < 4; ++j) {
                std::cout << (j + 1) << " - " << cidadesDisponiveis[j]
                          << (cidadeOcupada[j] ? " (indisponivel)" : "") << '\n';
            }
            std::cout << "Opcao: ";
            escolhaCidade = lerOpcao();
            if (escolhaCidade < 1 || escolhaCidade > 4 || cidadeOcupada[escolhaCidade - 1])
                std::cout << "Escolha invalida ou cidade ja selecionada. Tente novamente.\n";
        }
        cidadeOcupada[escolhaCidade - 1] = true;
        partida->adicionarCidade(nome, cidadesDisponiveis[escolhaCidade - 1]);
    }
    cidade = partida->getCidadeAtual();
    std::cout << "\nNova partida iniciada com " << quantidade << " jogador(es)!\n";
    cidade->exibirStatus();
}

void Menu::exibirStatus() {
    if (!exigirJogoEmAndamento()) return;
    cidade->exibirStatus();
}

void Menu::exibirSobre() {
    std::cout << "\nBolonha e Milano e um jogo de estrategia economica medieval desenvolvido em C++.\n";
}

void Menu::abrirMercado() {
    if (!exigirJogoEmAndamento()) return;

    int opcao;
    do {
        std::cout << "\n========== MERCADO ==========\n";
        std::cout << "Florins disponiveis: "
                  << cidade->getFlorins() << '\n';
        std::cout << "Preco do grao: "
                  << mercado.getPrecoGrao() << " florins\n";
        std::cout << "Preco da terra: "
                  << mercado.getPrecoTerra() << " florins/hectare\n";
        std::cout << "1 - Comprar graos\n";
        std::cout << "2 - Vender graos\n";
        std::cout << "3 - Comprar terras\n";
        std::cout << "4 - Vender terras\n";
        std::cout << "0 - Voltar\n";
        std::cout << "Escolha uma opcao: ";

        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                comprarGraos();
                break;
            case 2:
                venderGraos();
                break;
            case 3:
                comprarTerras();
                break;
            case 4:
                venderTerras();
                break;
            case 0:
                break;
            default:
                std::cout << "\nOpcao invalida!\n";
                break;
        }
    } while (opcao != 0);
}

void Menu::comprarGraos() {
    int quantidade = lerQuantidade();

    if (mercado.comprarGraos(*cidade, quantidade)) {
        std::cout << "Compra de graos realizada!\n";
    } else {
        std::cout << "Compra recusada. Verifique quantidade e saldo.\n";
    }
}

void Menu::venderGraos() {
    int quantidade = lerQuantidade();

    if (mercado.venderGraos(*cidade, quantidade)) {
        std::cout << "Venda de graos realizada!\n";
    } else {
        std::cout << "Venda recusada. Verifique quantidade e estoque.\n";
    }
}

void Menu::comprarTerras() {
    int quantidade = lerQuantidade();

    if (mercado.comprarTerras(*cidade, quantidade)) {
        std::cout << "Compra de terras realizada!\n";
    } else {
        std::cout << "Compra recusada. Verifique quantidade e saldo.\n";
    }
}

void Menu::venderTerras() {
    int quantidade = lerQuantidade();

    if (mercado.venderTerras(*cidade, quantidade)) {
        std::cout << "Venda de terras realizada!\n";
    } else {
        std::cout << "Venda recusada. Verifique quantidade e estoque.\n";
    }
}


void Menu::abrirAgricultura() {
    if (!exigirJogoEmAndamento()) return;

    int opcao;

    do {
        std::cout << "\n======= AGRICULTURA =======\n";
        std::cout << "Terras: " << cidade->getTerras()
                  << " hectares\n";
        std::cout << "Servos: " << cidade->getServos() << '\n';
        std::cout << "Graos: " << cidade->getGraos() << '\n';

        std::cout << "\n1 - Colher (processar safra)\n";
        std::cout << "2 - Distribuir alimentos\n";
        std::cout << "0 - Voltar ao menu principal\n";
        std::cout << "Escolha uma opcao: ";

        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                colher();
                break;

            case 2:
                distribuirAlimentos();
                break;

            case 0:
                std::cout << "Voltando ao menu principal...\n";
                break;

            default:
                std::cout << "Opcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}

void Menu::colher() {
    int hectares = agricultura.processarColheita(*cidade);
    if (hectares == -1) {
        std::cout << "\nEsta cidade ja realizou a colheita neste ano.\n";
    } else {
        std::cout << "\nColheita realizada!\nHectares cultivados: " << hectares
                  << "\nGraos apos a colheita: " << cidade->getGraos() << '\n';
    }
}

void Menu::distribuirAlimentos() {
    std::cout << "Percentual de graos para distribuir (20 a 80): ";

    int percentual = lerOpcao();

    if (agricultura.distribuirAlimentos(*cidade, percentual)) {
        std::cout << "\nAlimentos distribuidos!\n";
        std::cout << "Populacao atual: "
                  << cidade->getServos() << '\n';
        std::cout << "Graos restantes: "
                  << cidade->getGraos() << '\n';
    } else {
        std::cout << "\nPercentual invalido! Use de 20 a 80.\n";
    }
}

void Menu::abrirGoverno() {
    if (!exigirJogoEmAndamento()) return;

    int opcao;

    do {
        std::cout << "\n========== GOVERNO ==========\n";

        std::cout << "Florins disponiveis: "
                  << cidade->getFlorins() << '\n';

        std::cout << "Servos: "
                  << cidade->getServos() << '\n';

        std::cout << "Taxa de imposto: "
                  << cidade->getTaxaImposto() << "%\n";

        std::cout << "Nivel de justica: "
                  << cidade->getNivelJustica() << '\n';

        std::cout << "\n1 - Arrecadar impostos\n";
        std::cout << "2 - Definir taxa de imposto\n";
        std::cout << "3 - Definir nivel de justica\n";
        std::cout << "0 - Voltar ao menu principal\n";

        std::cout << "Escolha uma opcao: ";

        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                arrecadarImpostos();
                break;

            case 2:
                definirTaxaImposto();
                break;

            case 3:
                definirJustica();
                break;

            case 0:
                std::cout << "\nVoltando ao menu principal...\n";
                break;

            default:
                std::cout << "\nOpcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}

void Menu::arrecadarImpostos() {
    int arrecadado = governo.arrecadarImpostos(*cidade);
    if (arrecadado == -1) {
        std::cout << "\nOs impostos desta cidade ja foram arrecadados neste ano.\n";
        return;
    }
    std::cout << "\nArrecadacao realizada!\nFlorins arrecadados: " << arrecadado
              << "\nTotal de florins no tesouro: " << cidade->getFlorins() << '\n';
}

void Menu::definirTaxaImposto() {
    std::cout << "\n========== DEFINIR IMPOSTO ==========\n";

    std::cout << "Taxa atual: "
              << cidade->getTaxaImposto() << "%\n";

    std::cout << "Digite a nova taxa de imposto (0 a 50): ";

    int taxa = lerOpcao();

    if (governo.definirTaxaImposto(*cidade, taxa)) {
        std::cout << "\nTaxa de imposto atualizada com sucesso!\n";
        std::cout << "Nova taxa: "
                  << cidade->getTaxaImposto() << "%\n";
    } else {
        std::cout << "\nTaxa invalida! Informe um valor entre 0 e 50.\n";
    }
}

void Menu::definirJustica() {
    std::cout << "\n========== DEFINIR JUSTICA ==========\n";

    std::cout << "Nivel atual: "
              << cidade->getNivelJustica() << '\n';

    std::cout << "\nEscolha o novo nivel de justica:\n";
    std::cout << "1 - Justa\n";
    std::cout << "2 - Moderada\n";
    std::cout << "3 - Severa\n";
    std::cout << "Opcao: ";

    int opcao = lerOpcao();

    std::string nivel;

    switch (opcao) {
        case 1:
            nivel = "Justa";
            break;

        case 2:
            nivel = "Moderada";
            break;

        case 3:
            nivel = "Severa";
            break;

        default:
            std::cout << "\nOpcao invalida!\n";
            return;
    }

    if (governo.definirJustica(*cidade, nivel)) {
        std::cout << "\nNivel de justica atualizado com sucesso!\n";
        std::cout << "Novo nivel: "
                  << cidade->getNivelJustica() << '\n';
    } else {
        std::cout << "\nNao foi possivel alterar o nivel de justica.\n";
    }
}

void Menu::abrirConstrucoes() {
    if (!exigirJogoEmAndamento()) return;

    int opcao;

    do {
        std::cout << "\n========== CONSTRUCOES ==========\n";

        std::cout << "Florins disponiveis: "
                  << cidade->getFlorins() << '\n';

        std::cout << "Servos disponiveis: "
                  << cidade->getServos() << '\n';

        std::cout << "Soldados atuais: "
                  << cidade->getSoldados() << '\n';

        std::cout << "Construcoes atuais: "
                  << cidade->getConstrucoes() << '\n';

        std::cout << "\n1 - Recrutar soldados\n";
        std::cout << "2 - Construir edificios\n";
        std::cout << "0 - Voltar ao menu principal\n";

        std::cout << "Escolha uma opcao: ";

        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                recrutarSoldados();
                break;

            case 2:
                construir();
                break;

            case 0:
                std::cout << "\nVoltando ao menu principal...\n";
                break;

            default:
                std::cout << "\nOpcao invalida!\n";
                break;
        }

    } while (opcao != 0);
}

void Menu::recrutarSoldados() {
    int quantidade = lerQuantidade();

    if (construcoes.recrutarSoldados(*cidade, quantidade)) {
        std::cout << "\nRecrutamento realizado com sucesso!\n";

        std::cout << "Soldados atuais: "
                  << cidade->getSoldados() << '\n';

        std::cout << "Servos restantes: "
                  << cidade->getServos() << '\n';

        std::cout << "Florins restantes: "
                  << cidade->getFlorins() << '\n';
    } else {
        std::cout << "\nRecrutamento recusado!\n";
        std::cout << "Verifique a quantidade de florins e servos.\n";
    }
}

void Menu::construir() {
    int quantidade = lerQuantidade();

    if (construcoes.construir(*cidade, quantidade)) {
        std::cout << "\nConstrucao realizada com sucesso!\n";

        std::cout << "Construcoes atuais: "
                  << cidade->getConstrucoes() << '\n';

        std::cout << "Florins restantes: "
                  << cidade->getFlorins() << '\n';
    } else {
        std::cout << "\nConstrucao recusada!\n";
        std::cout << "Verifique a quantidade e o saldo de florins.\n";
    }
}



void Menu::exibirClassificacao() {
    if (!exigirJogoEmAndamento()) return;
    std::cout << "\n============= CLASSIFICACAO =============\n";
    for (const auto& c : partida->getCidades()) {
        int prestigio = nobreza.calcularPrestigio(*c);
        int falta = nobreza.prestigioParaProximoTitulo(*c->getDono());
        std::cout << c->getDono()->getNome() << " | " << c->getNome()
                  << " | " << c->getDono()->getTitulo()
                  << " | Prestigio: " << prestigio;
        if (falta < 0) std::cout << " | Monarca";
        else std::cout << " | Faltam: " << (prestigio >= falta ? 0 : falta - prestigio)
                       << " para o proximo titulo";
        std::cout << '\n';
    }
    std::cout << "==========================================\n";
}

void Menu::encerrarTurno() {
    if (!exigirJogoEmAndamento()) return;
    bool anoEncerrado = partida->passarTurno();
    if (!anoEncerrado) {
        cidade = partida->getCidadeAtual();
        std::cout << "\nTurno encerrado. Agora e a vez de " << cidade->getDono()->getNome()
                  << " (" << cidade->getNome() << ").\n";
        return;
    }

    std::cout << "\nTodos os jogadores encerraram seus turnos. Fechando o ano...\n";
    auto promovidas = partida->encerrarAno(nobreza);
    for (Cidade* c : promovidas) {
        std::cout << c->getDono()->getNome() << " foi promovido(a) a "
                  << c->getDono()->getTitulo() << "!\n";
    }
    exibirClassificacao();
    if (partida->terminou()) { encerrarPartida(); return; }
    cidade = partida->getCidadeAtual();
    std::cout << "Novo ano: " << partida->getAnoAtual() << ". Comeca a vez de "
              << cidade->getDono()->getNome() << ".\n";
}

void Menu::encerrarPartida() {
    Cidade* vencedor = partida->determinarVencedor(nobreza);
    if (vencedor) {
        std::cout << "\n========== FIM DE JOGO ==========\nVencedor: "
                  << vencedor->getDono()->getNome() << " - " << vencedor->getNome()
                  << " (" << vencedor->getDono()->getTitulo() << ")\nPrestigio: "
                  << nobreza.calcularPrestigio(*vencedor) << '\n';
    }
    std::cout << "=================================\n";
    partida.reset();
    cidade = nullptr;
}
