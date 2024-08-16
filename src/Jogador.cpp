#include "Jogador.hpp"
#include <limits>
#include <iostream>

Jogador::Jogador(const std::string& apelido, const std::string& nome) : apelido(apelido), nome(nome) {}

//Jogador::Jogador(std::string apelido, std::string nome) : apelido(apelido), nome(nome) {}

std::string Jogador::getApelido() const {
    return this->apelido;
}

std::string Jogador::getNome() const {
    return this->nome;
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

void Jogador::salvar(std::ofstream& out) const {
  out << apelido << '\n' << nome << '\n';
  for (const auto& jogo : this->estatisticas) {
      out << jogo.first << ' ' << jogo.second[0] << ' ' << jogo.second[1] << ' ' << jogo.second[2] << '\n';
  }
  out << "---\n";
}

void Jogador::carregar(std::ifstream& in) {
  std::getline(in, this->apelido);
  std::getline(in, this->nome);
  this->estatisticas.clear();
  std::string jogo;
  int v, d, e;
  while (in >> jogo >> v >> d >> e) {
      this->estatisticas[jogo] = {v, d, e};
  }
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}