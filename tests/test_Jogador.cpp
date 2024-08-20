#include "doctest.h"
#include "Jogador.hpp"
#include <iostream>
#include <string>
#include <map>
#include <array>
#include <fstream>
#include <sstream>

TEST_CASE("Teste da classe Jogador") {
  Jogador jogador("apelido", "nome do jogador");
  
  SUBCASE("Teste getApelido() e getNome()") {
    CHECK(jogador.getApelido() == "apelido");
    CHECK(jogador.getNome() == "nome do jogador");
  }

  SUBCASE("Teste de setEstatistica() e listarEstatisticas()"){
    jogador.setEstatistica("jogo1", 0); // vitória jogo1
    jogador.setEstatistica("jogo1", 0); // vitória jogo1
    jogador.setEstatistica("jogo1", 1); // derrota jogo1
    jogador.setEstatistica("jogo1", 2); // empate jogo1
    jogador.setEstatistica("jogo2", 0); // vitória jogo2;

    // redirecionar o output do terminal para a string oss
    std::ostringstream oss;
    // salvar o buffer original
    std::streambuf* coutbuf = std::cout.rdbuf();
    // redirecionar o output para a string oss
    std::cout.rdbuf(oss.rdbuf());

    jogador.listarEstatisticas();

    // restaurando o buffer
    std::cout.rdbuf(coutbuf);

    std::string saida_esperada = 
      "apelido nome do jogador\n"
      "jogo1 - V: 2 D: 1 E: 1\n"
      "jogo2 - V: 1 D: 0 E: 0\n";

    CHECK(oss.str() == saida_esperada);
  }
}