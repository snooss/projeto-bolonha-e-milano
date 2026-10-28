
#include "Menu.h"

using namespace std;

// Construtor
Menu::Menu() {
    emExecucao = true;
}

// Metodo principal do menu
void Menu::executar() {
    while (emExecucao) {
        exibirOpcoes();

        int opcao = lerOpcao();

        processarOpcao(opcao);
    }

    cout << "\nJogo encerrado. Ate mais!\n";
}

// Mostra as opcoes
void Menu::exibirOpcoes() {
    cout << "\n==========================================\n";
    cout << "             BOLONHA E MILANO\n";
    cout << " Um jogo de estrategia economica medieval\n";
    cout << "==========================================\n";
    cout << "1 - Novo jogo\n";
    cout << "2 - Sobre o jogo\n";
    cout << "0 - Sair\n";
    cout << "Escolha uma opcao: ";
}

// Le a opcao do jogador
int Menu::lerOpcao() {
    int opcao;

    if (cin >> opcao) {
        return opcao;
    }

    cin.clear();
    cin.ignore(10000, '\n');

    return -1;
}

// Decide o que fazer
void Menu::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            cout << "\nNovo jogo sera implementado na Etapa 2.\n";
            break;

        case 2:
            exibirSobre();
            break;

        case 0:
            emExecucao = false;
            break;

        default:
            cout << "\nOpcao invalida! Digite 1, 2 ou 0.\n";
            break;
    }
}

// Mostra informacoes sobre o jogo
void Menu::exibirSobre() {
    cout << "\n========== SOBRE O JOGO ==========\n";
    cout << "Bolonha e Milano e um jogo de estrategia\n";
    cout << "economica medieval desenvolvido em C++.\n";
    cout << "O objetivo sera administrar uma cidade,\n";
    cout << "gerenciar recursos e tomar decisoes.\n";
    cout << "As regras serao implementadas nas proximas etapas.\n";
}
