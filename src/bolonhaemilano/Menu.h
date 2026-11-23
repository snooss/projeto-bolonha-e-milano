#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>
#include "Partida.h"
#include "Mercado.h"
#include "Agricultura.h"
#include "Governo.h"
#include "Construcoes.h"
#include "Nobreza.h"

class Menu {
private:
    bool emExecucao;
    std::unique_ptr<Partida> partida;
    Cidade* cidade;
    Mercado mercado;
    Agricultura agricultura;
    Governo governo;
    Construcoes construcoes;
    Nobreza nobreza;

    void iniciarNovoJogo();
    void limparTela();
    void pausar();
    void exibirOpcoes();
    int lerOpcao();
    int lerQuantidade();
    int lerInteiro();
    bool exigirJogoEmAndamento();
    void processarOpcao(int opcao);
    void exibirSobre();
    void exibirStatus();
    void abrirMercado(); void comprarGraos(); void venderGraos(); void comprarTerras(); void venderTerras();
    void abrirAgricultura(); void colher(); void distribuirAlimentos();
    void abrirGoverno(); void arrecadarImpostos(); void definirTaxaImposto(); void definirJustica();
    void abrirConstrucoes(); void recrutarSoldados(); void construir();
    void encerrarTurno();
    void exibirClassificacao();
    void encerrarPartida();

public:
    Menu();
    void executar();
};

#endif
