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

  std::map<std::string,std::unique_ptr<Jogador>> jogadores;

public:
  Jogada() = default;
  void carregarJogadores(std::string);
  void salvarJogadores(std::string) const;
  void adicionarJogador(std::string, std::string);
  void removerJogador(std::string, std::string);
  void listarJogadores() const;
  Jogador* selecionarJogador(std::string apelido) const;
  const std::map<std::string, std::unique_ptr<Jogador>>& getJogadores() const;

};

#endif // JOGADA_HPP