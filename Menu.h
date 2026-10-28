
#ifndef MENU_H
#define MENU_H

#include <memory>
#include "Jogador.h"
#include "Cidade.h"

class Menu {
private:
    bool emExecucao;

    std::unique_ptr<Jogador> jogador;
    std::unique_ptr<Cidade> cidade;

    void iniciarNovoJogo();
    void exibirOpcoes();
    int lerOpcao();
    void processarOpcao(int opcao);
    void exibirSobre();
    void exibirStatus();

public:
    Menu();
    void executar();
};

#endif
