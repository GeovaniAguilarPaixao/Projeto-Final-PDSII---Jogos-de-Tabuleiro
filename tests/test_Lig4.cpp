#include "doctest.h"
#include "Lig4.hpp"

TEST_CASE("Testes da classe Lig4") {
    // Cria o jogo lig4
    Lig4 jogo;

    SUBCASE("Teste jogadaValida()") {
        CHECK(jogo.jogadaValida(0));  // Primeira coluna deve ser válida
        CHECK_FALSE(jogo.jogadaValida(8));  // Coluna inexistente
        // Preenche a coluna 0
        for (int i = 0; i < 6; ++i) {
            jogo.fazerJogada(0, 'X');
        }
        CHECK_FALSE(jogo.jogadaValida(0));  // Coluna deve ser inválida por estar cheia
    }

    SUBCASE("Teste verificarVitoria() horizontal") {
        // Preenche o tabuleiro com uma vitória horizontal
        for (int i = 0; i < 4; ++i) {
            jogo.fazerJogada(i, 'X');
        }
        CHECK(jogo.verificarVitoria('X'));
    }

    SUBCASE("Testa verificarVitoria() vertical") {
        // Preenche o tabuleiro com uma vitória vertical
        for (int i = 0; i < 4; ++i) {
            jogo.fazerJogada(1, 'O');
        }
        CHECK(jogo.verificarVitoria('O'));
    }

    SUBCASE("Testa verificarVitoria() diagonal") {
        // Preenche o tabuleiro com uma vitória diagonal
        jogo.fazerJogada(0, 'X');
        jogo.fazerJogada(1, 'O');
        jogo.fazerJogada(1, 'X');
        jogo.fazerJogada(2, 'O');
        jogo.fazerJogada(3, 'X');
        jogo.fazerJogada(2, 'O');
        jogo.fazerJogada(2, 'X');
        jogo.fazerJogada(3, 'O');
        jogo.fazerJogada(4, 'X');
        jogo.fazerJogada(3, 'O');
        jogo.fazerJogada(3, 'X');

        CHECK(jogo.verificarVitoria('X'));  // Deve haver uma vitória diagonal
    }

    SUBCASE("Teste tabuleiroCheio()") {
        // Preenche o tabuleiro completamente
        for (int coluna = 0; coluna < 7; ++coluna) {
            for (int linha = 0; linha < 6; ++linha) {
                jogo.fazerJogada(coluna, 'X');
            }
        }
        CHECK(jogo.tabuleiroCheio());
    }
}
