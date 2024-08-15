#include "Jogador.hpp"

#include <iostream>

Jogador::Jogador(std::string apelido, std::string nome) : apelido(apelido), nome(nome) {}

std::string Jogador::getApelido() const {
    return apelido;
}

std::string Jogador::getNome() const {
    return nome;
}

void Jogador::listarEstatisticas() const {
    std::cout << this->apelido << " " << this->nome << std::endl;
    for (const auto& jogo : this->estatisticas) {
      std::cout << jogo.first << " - V: " << jogo.second[0] << " D: " << jogo.second[1] << " E: " << jogo.second[2] << std::endl;
    }
}

void Jogador::setEstatistica(std::string jogo, int resultado) {
  if (this->estatisticas.find(jogo) != this->estatisticas.end()) {
    this->estatisticas[jogo][resultado]++;
  }
  else {
    this->estatisticas[jogo] = {0, 0, 0};
    this->estatisticas[jogo][resultado]++;
  }
}