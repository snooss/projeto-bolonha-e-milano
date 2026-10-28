
#ifndef MENU_H
#define MENU_H

#include <memory>
#include "Jogador.h"
#include "Cidade.h"
#include "Mercado.h"
#include "Agricultura.h"

class Menu {
private:
    bool emExecucao;

    std::unique_ptr<Jogador> jogador;
    std::unique_ptr<Cidade> cidade;
    Mercado mercado;
    Agricultura agricultura;

    void iniciarNovoJogo();
    void exibirOpcoes();
    int lerOpcao();
    int lerQuantidade();
    void processarOpcao(int opcao);
    void exibirSobre();
    void exibirStatus();

    void abrirMercado();
    void comprarGraos();
    void venderGraos();
    void comprarTerras();
    void venderTerras();
    void abrirAgricultura();
    void colher();
    void distribuirAlimentos();

public:
    Menu();
    void executar();
};

#endif
