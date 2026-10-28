
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

    std::cout << "\nJogo encerrado. Ate mais!\n";
}

void Menu::exibirOpcoes() {
    std::cout << "\n==========================================\n";
    std::cout << "             BOLONHA E MILANO\n";
    std::cout << " Um jogo de estrategia economica medieval\n";
    std::cout << "==========================================\n";
    std::cout << "1 - Novo jogo\n";
    std::cout << "2 - Ver status da cidade\n";
    std::cout << "3 - Sobre o jogo\n";
    std::cout << "0 - Sair\n";
    std::cout << "Escolha uma opcao: ";
}

int Menu::lerOpcao() {
    std::string entrada;
    std::getline(std::cin, entrada);

    try {
        std::size_t posicao;
        int opcao = std::stoi(entrada, &posicao);

        // Rejeita entradas como "2abc"
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

void Menu::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            iniciarNovoJogo();
            break;

        case 2:
            exibirStatus();
            break;

        case 3:
            exibirSobre();
            break;

        case 0:
            emExecucao = false;
            break;

        default:
            std::cout << "\nOpcao invalida! Digite 1, 2, 3 ou 0.\n";
            break;
    }
}

void Menu::iniciarNovoJogo() {
    std::string nomeJogador;
    std::string nomeCidade;

    std::cout << "\nDigite o nome do jogador: ";
    std::getline(std::cin, nomeJogador);

    std::cout << "Digite o nome da cidade: ";
    std::getline(std::cin, nomeCidade);

    if (nomeJogador.find_first_not_of(" \t\r\n") == std::string::npos ||
        nomeCidade.find_first_not_of(" \t\r\n") == std::string::npos) {
        std::cout << "\nOs nomes nao podem ficar vazios.\n";
        return;
    }

    jogador = std::make_unique<Jogador>(nomeJogador);

    cidade = std::make_unique<Cidade>(
        nomeCidade,
        jogador.get()
    );

    std::cout << "\nNovo jogo iniciado com sucesso!\n";

    cidade->exibirStatus();
}

void Menu::exibirStatus() {
    if (cidade == nullptr) {
        std::cout << "\nNenhum jogo foi iniciado ainda.\n";
        std::cout << "Escolha 1 para iniciar um novo jogo.\n";
        return;
    }

    cidade->exibirStatus();
}

void Menu::exibirSobre() {
    std::cout << "\n========== SOBRE O JOGO ==========\n";
    std::cout << "Bolonha e Milano e um jogo de estrategia\n";
    std::cout << "economica medieval desenvolvido em C++.\n";
    std::cout << "Seu objetivo sera administrar uma cidade,\n";
    std::cout << "gerenciar recursos e tomar decisoes.\n";
    std::cout << "As regras serao implementadas nas proximas etapas.\n";
}
