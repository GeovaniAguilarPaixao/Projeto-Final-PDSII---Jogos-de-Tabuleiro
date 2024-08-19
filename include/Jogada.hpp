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
  // valor: ponteiro inteligente único para o objeto Jogador
  std::map<std::string,std::unique_ptr<Jogador>> jogadores;

public:
  Jogada() = default;
  // Carrega os dados de todos os jogadores dos arquivos no diretório /data
  void carregarJogadores(std::string);
  // Salva os dados de todos os jogadores dos arquivos no diretório /data
  void salvarJogadores(std::string) const;
  // Adiciona um jogador à jogada
  void adicionarJogador(std::string, std::string);
  // Remove um jogador da jogada
  void removerJogador(std::string, std::string);
  // Lista os dados dos jogadores da jogada
  void listarJogadores() const;
  // Seleciona um jogador da jogada
  Jogador* selecionarJogador(std::string apelido) const;
  const std::map<std::string, std::unique_ptr<Jogador>>& getJogadores() const;

};

#endif // JOGADA_HPP