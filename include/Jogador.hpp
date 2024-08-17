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
  // <jogo,{int_vitoria, int_derrota, int_empate}>
  std::map<std::string, std::array<int, 3>> estatisticas;

public:
 Jogador(const std::string& apelido, const std::string& nome);
 Jogador() = default;  // Construtor padrão para leitura de arquivos
 ~Jogador() = default;
  //Jogador(std::string, std::string);
  //~Jogador();
  std::string getApelido() const;
  std::string getNome() const;
  void listarEstatisticas() const;
  void setEstatistica(std::string, int);
  void salvar(std::ofstream& out) const;
  void carregar(std::ifstream& in);
  
};

#endif // JOGADOR_HPP