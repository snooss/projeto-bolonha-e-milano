
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

#include "Menu.h"

Menu::Menu() {
    emExecucao = true;
}

void Menu::executar() {
    while (emExecucao) {
        exibirOpcoes();
        int opcao = lerOpcao();
        processarOpcao(opcao);
    }

    std::cout << "\nJogo encerrado. Ate nunca mais!\n";
}

void Menu::exibirOpcoes() {
    std::cout << "\n==========================================\n";
    std::cout << "             BOLONHA E MILANO\n";
    std::cout << " Um jogo de estrategia economica medieval\n";
    std::cout << "==========================================\n";
    std::cout << "1 - Novo jogo\n";
    std::cout << "2 - Ver status da cidade\n";
    std::cout << "3 - Mercado\n";
    std::cout << "4 - Agricultura\n";
    std::cout << "5 - Sobre o jogo\n";
    std::cout << "0 - Sair\n";
    std::cout << "Escolha uma opcao: ";
}

int Menu::lerOpcao() {
    std::string entrada;
    std::getline(std::cin, entrada);

    try {
        std::size_t posicao;
        int opcao = std::stoi(entrada, &posicao);

        if (entrada.find_first_not_of(" \t\r\n", posicao)
            != std::string::npos) {
            return -1;
        }

        return opcao;
    } catch (const std::invalid_argument&) {
        return -1;
    } catch (const std::out_of_range&) {
        return -1;
    }
}

int Menu::lerQuantidade() {
    std::cout << "Digite a quantidade: ";
    return lerOpcao();
}

void Menu::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            iniciarNovoJogo();
            break;
        case 2:
            exibirStatus();
            break;
        case 3:
            abrirMercado();
            break;
        case 4:
            abrirAgricultura();
            break;
        case 5:
            exibirSobre();
            break;
        case 0:
            emExecucao = false;
            break;
        default:
            std::cout << "\nOpcao invalida!\n";
            break;
    }
}

void Menu::iniciarNovoJogo() {
    std::string nomeJogador;
    std::string nomeCidade;

    std::cout << "\nDigite o nome do jogador: ";
    std::getline(std::cin, nomeJogador);

    std::cout << "Digite o nome da cidade (Bolonha ou Milano): ";
    std::getline(std::cin, nomeCidade);

    if (nomeJogador.find_first_not_of(" \t\r\n") ==
            std::string::npos ||
        nomeCidade.find_first_not_of(" \t\r\n") ==
            std::string::npos) {
        std::cout << "\nOs nomes nao podem ficar vazios.\n";
        return;
    }

    jogador = std::make_unique<Jogador>(nomeJogador);
    cidade = std::make_unique<Cidade>(
        nomeCidade, jogador.get()
    );

    std::cout << "\nNovo jogo iniciado!\n";
    cidade->exibirStatus();
}

void Menu::exibirStatus() {
    if (!cidade) {
        std::cout << "\nNenhum jogo foi iniciado ainda.\n";
        return;
    }

    cidade->exibirStatus();
}

void Menu::exibirSobre() {
    std::cout << "\nBolonha e Milano é um jogo de estrategia\n";
    std::cout << "economica medieval desenvolvido em C++.\n";
}

void Menu::abrirMercado() {
    if (!cidade) {
        std::cout << "\nInicie um jogo antes de acessar o mercado.\n";
        return;
    }

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
    if (!cidade) {
        std::cout << "\nInicie um jogo primeiro!\n";
        return;
    }

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

    if (hectares > 0) {
        std::cout << "\nColheita realizada!\n";
        std::cout << "Hectares cultivados: "
                  << hectares << '\n';
        std::cout << "Graos apos a colheita: "
                  << cidade->getGraos() << '\n';
    } else {
        std::cout << "\nNao foi possivel realizar a colheita.\n";
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

