#include "Jogador.hpp"
#include <limits>
#include <iostream>

Jogador::Jogador(const std::string& apelido, const std::string& nome) : apelido(apelido), nome(nome) {}

std::string Jogador::getApelido() const {
    return this->apelido;
}

std::string Jogador::getNome() const {
    return this->nome;
}

// Imprime as estatísticas do jogador
void Jogador::listarEstatisticas() const {
    std::cout << this->apelido << " " << this->nome << std::endl;
    // iterador para percorrer o map
    // jogo.first -> nome do jogo
    // jogo.second -> array com 3 posições ([0]=num_vitorias [1]=num_derrotas [2]=num_empates)
    for (const auto& jogo : this->estatisticas) {
      std::cout << jogo.first << " - V: " << jogo.second[0] << " D: " << jogo.second[1] << " E: " << jogo.second[2] << std::endl;
    }
}

// Adiciona estatísticas ao jogador
// Recebe como parâmetros o (nome do jogo) e o (resultado), sendo:
// 0: +1 vitória
// 1: +1 derrota
// 2: +1 empate
void Jogador::setEstatistica(std::string jogo, int resultado) {
  // Verifica se o jogo já existe no map
  if (this->estatisticas.find(jogo) != this->estatisticas.end()) {
    // Incrementa o numero de vitorias/derrotas/empates ao jogo
    this->estatisticas[jogo][resultado]++;
  }
  // Caso o jogo não exista no map
  else {
    // Adiciona uma nova chave no map com o nome do jogo
    // Adicionar o array com as vitorias/derrotas/empates zeradas
    this->estatisticas[jogo] = {0, 0, 0};
    // Incrementa o numero de vitoria/derrota/empate ao jogo
    this->estatisticas[jogo][resultado]++;
  }
}

// Salva os dados do jogador em um arquivo
// Recebe como parâmetro o fluxo de saída do arquivo a ser salvo
void Jogador::salvar(std::ofstream& out) const {
  // Salva o apelido na primeira linha
  // Salva o nome na segunda linha
  out << apelido << '\n' << nome << '\n';
  // Iterador para o map de estatísticas
  // jogo.first -> nome do jogo
  // jogo.second -> array com 3 posições ([0]=num_vitorias [1]=num_derrotas [2]=num_empates)
  for (const auto& jogo : this->estatisticas) {
      // Salva em cada linha o nome do jogo seguido do número de vitórias, derrotas e empates
      out << jogo.first << ' ' << jogo.second[0] << ' ' << jogo.second[1] << ' ' << jogo.second[2] << '\n';
  }
  // Indica o final de dados "úteis" no arquivo
  out << "---\n";
}

// Carrega os dados do jogador de um arquivo
// Recebe como parâmetro o fluxo de entrada do arquivo a ser carregado
void Jogador::carregar(std::ifstream& in) {
  // Lê o apelido na primeira linha
  std::getline(in, this->apelido);
  // Lê o nome na segunda linha
  std::getline(in, this->nome);
  // Zera as estatísticas do jogador
  this->estatisticas.clear();
  // Variáveis auxiliares para leitura das estatísticas do arquivo
  std::string jogo;
  int v, d, e;
  // Lê o nome do jogo e o número de vitórias, derrotas e empates em cada linha
  while (in >> jogo >> v >> d >> e) {
      // Salva as estatísticas de cada jogo no map
      this->estatisticas[jogo] = {v, d, e};
  }
  // Ignora linhas extras que podem constar no arquivo
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

// Retorna o map com as estatísticas do jogador
std::map<std::string, std::array<int, 3>> Jogador::getEstatisticas() const{
  return this->estatisticas;
}