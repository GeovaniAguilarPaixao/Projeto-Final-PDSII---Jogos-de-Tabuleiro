#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <string>
#include <map>
#include <array>
#include <fstream>

class Jogador {
private:

  std::string apelido;
  std::string nome;
  // map<nome_jogo, {int_vitorias, int_derrotas, int empates}>. Container para armazenar as estatísticas do jogador. Consiste em um map no qual a chave é o nome jogo e o valor é um array com 3 posições. A primeira posição armazena o número de vitórias, a segunda o de derrotas e a terceira o de empates.
  std::map<std::string, std::array<int, 3>> estatisticas;

public:
 Jogador(const std::string& apelido, const std::string& nome);
 Jogador() = default;  // Construtor padrão para leitura de arquivos
 ~Jogador() = default;
  std::string getApelido() const;
  std::string getNome() const;
  // Imprime as estatísticas do jogador
  void listarEstatisticas() const;
  // Adiciona estatísticas ao jogador
  void setEstatistica(std::string, int);
  // Salva os dados do jogador em um arquivo
  void salvar(std::ofstream& out) const;
  // Carrega os dados do jogador de um arquivo
  void carregar(std::ifstream& in);
  
};

#endif // JOGADOR_HPP