#ifndef PARTIDA_H
#define PARTIDA_H

#include <memory>
#include <string>
#include <vector>
#include "Cidade.h"
#include "Nobreza.h"

class Partida {
private:
    static constexpr int MAXIMO_JOGADORES = 4;
    static constexpr int ANO_FINAL = 1410;
    std::vector<std::unique_ptr<Jogador>> jogadores;
    std::vector<std::unique_ptr<Cidade>> cidades;
    std::size_t indiceAtual;

public:
    Partida();
    bool adicionarCidade(const std::string& nomeJogador, const std::string& nomeCidade);
    const std::vector<std::unique_ptr<Cidade>>& getCidades() const;
    Cidade* getCidadeAtual() const;
    int getAnoAtual() const;
    int getAnoFinal() const;
    std::size_t getQuantidadeJogadores() const;
    bool passarTurno();
    std::vector<Cidade*> encerrarAno(const Nobreza& nobreza);
    bool terminou() const;
    Cidade* determinarVencedor(const Nobreza& nobreza) const;
};

#endif
