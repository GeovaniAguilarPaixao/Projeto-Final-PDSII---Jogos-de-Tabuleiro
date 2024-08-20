#include "doctest.h"
#include "Reversi.hpp"

TEST_CASE("Teste da classe Reversi") {
    // Cria o jogo Reversi
    Reversi jogo;

    SUBCASE("Teste jogadaValida()") {
        CHECK(jogo.jogadaValida(2, 3, 'X')); // Jogada válida
        CHECK_FALSE(jogo.jogadaValida(0, 0, 'X')); // Jogada inválida
    }

    SUBCASE("Teste fazerJogada()") {
        CHECK(jogo.fazerJogada(2, 3, 'X')); // Jogada válida
        CHECK_FALSE(jogo.fazerJogada(0, 0, 'X')); // jogada inválida
    }
}
