
#ifndef MENU_H
#define MENU_H

#include <iostream>

class Menu {
private:
    bool emExecucao;

    void exibirOpcoes();
    int lerOpcao();
    void processarOpcao(int opcao);
    void exibirSobre();

public:
    Menu();
    void executar();
};

#endif
