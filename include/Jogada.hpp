#ifndef JOGADA_HPP
#define JOGADA_HPP

#include <vector>
#include <map>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <memory>

#include "Jogador.hpp"

class Jogada {

private:
  // Armazena os jogadores da jogada em um map, no qual:
  // chave única: apelido do jogador
  // valor: ponteiro inteligente para o objeto Jogador
  std::map<std::string,std::shared_ptr<Jogador>> jogadores;

public:
  Jogada() = default;
  // Carrega os dados dos jogadores dos arquivos no diretório dir_data
  void carregarJogadores(std::string dir_data);
  // Salva os dados de todos os jogadores dos arquivos no diretório dir_data
  void salvarJogadores(std::string dir_data) const;
  // Adiciona um jogador à jogada
  void adicionarJogador(std::string apelido, std::string nome);
  // Remove um jogador da jogada
  void removerJogador(std::string apelido, std::string dir_data);
  // Lista os dados dos jogadores da jogada
  void listarJogadores() const;
  // Seleciona um jogador da jogada
  Jogador* selecionarJogador(std::string apelido) const;
  // Retorna um map com todos os jogadores
  const std::map<std::string, std::shared_ptr<Jogador>>& getJogadores() const;

};

#endif // JOGADA_HPP