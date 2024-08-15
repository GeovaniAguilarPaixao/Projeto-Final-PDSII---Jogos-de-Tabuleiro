#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <string>
#include <map>
#include <array>

class Jogador {
private:

  std::string apelido;
  std::string nome;
  // <jogo,{int_vitoria, int_derrota, int_empate}>
  std::map<std::string, std::array<int, 3>> estatisticas;

public:

  Jogador(std::string, std::string);
  ~Jogador();
  std::string getApelido() const;
  std::string getNome() const;
  void listarEstatisticas() const;

};

#endif // CLIENTE_HPP