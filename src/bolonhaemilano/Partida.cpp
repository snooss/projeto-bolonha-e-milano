#include "Partida.h"

Partida::Partida() : indiceAtual(0) {}

bool Partida::adicionarCidade(const std::string& nomeJogador, const std::string& nomeCidade) {
    if (cidades.size() >= MAXIMO_JOGADORES || nomeJogador.empty() || nomeCidade.empty()) return false;
    for (const auto& c : cidades) if (c->getNome() == nomeCidade) return false;
    jogadores.push_back(std::make_unique<Jogador>(nomeJogador));
    cidades.push_back(std::make_unique<Cidade>(nomeCidade, jogadores.back().get()));
    return true;
}

const std::vector<std::unique_ptr<Cidade>>& Partida::getCidades() const { return cidades; }
Cidade* Partida::getCidadeAtual() const {
    if (cidades.empty() || indiceAtual >= cidades.size()) return nullptr;
    return cidades[indiceAtual].get();
}
int Partida::getAnoAtual() const { return cidades.empty() ? 1400 : cidades.front()->getAnoAtual(); }
int Partida::getAnoFinal() const { return ANO_FINAL; }
std::size_t Partida::getQuantidadeJogadores() const { return cidades.size(); }

bool Partida::passarTurno() {
    if (cidades.empty()) return false;
    ++indiceAtual;
    if (indiceAtual >= cidades.size()) { indiceAtual = 0; return true; }
    return false;
}

std::vector<Cidade*> Partida::encerrarAno(const Nobreza& nobreza) {
    std::vector<Cidade*> promovidas;
    for (const auto& cidade : cidades) {
        cidade->avancarAno();
        if (nobreza.verificarPromocao(*cidade)) promovidas.push_back(cidade.get());
    }
    return promovidas;
}

bool Partida::terminou() const {
    if (cidades.empty()) return false;
    for (const auto& cidade : cidades) {
        if (cidade->getDono()->ehMonarca()) return true;
    }
    return getAnoAtual() > ANO_FINAL;
}

Cidade* Partida::determinarVencedor(const Nobreza& nobreza) const {
    if (cidades.empty()) return nullptr;
    Cidade* vencedor = cidades.front().get();
    for (const auto& ptr : cidades) {
        Cidade* atual = ptr.get();
        int nivelAtual = atual->getDono()->getNivelTitulo();
        int nivelVencedor = vencedor->getDono()->getNivelTitulo();
        if (nivelAtual > nivelVencedor ||
            (nivelAtual == nivelVencedor && nobreza.calcularPrestigio(*atual) > nobreza.calcularPrestigio(*vencedor))) {
            vencedor = atual;
        }
    }
    return vencedor;
}
