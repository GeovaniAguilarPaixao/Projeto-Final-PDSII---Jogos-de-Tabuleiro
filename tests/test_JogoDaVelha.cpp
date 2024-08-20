#include "JogoDaVelha.hpp"
#include "doctest.h"

TEST_CASE("Teste da classe JogoDaVelha") {
    // Cria o jogo da velha
    JogoDaVelha jogo;

    SUBCASE("Teste verificarVitoria()") {
        // Testa vitória em uma linha
        jogo.fazerJogada(0, 0, 'X');
        jogo.fazerJogada(0, 1, 'X');
        jogo.fazerJogada(0, 2, 'X');
        CHECK(jogo.verificarVitoria('X'));

        // Reinicia o jogo
        jogo = JogoDaVelha();

        // Testa vitória em uma coluna
        jogo.fazerJogada(0, 0, 'O');
        jogo.fazerJogada(1, 0, 'O');
        jogo.fazerJogada(2, 0, 'O');
        CHECK(jogo.verificarVitoria('O'));

        // Reinicia o jogo
        jogo = JogoDaVelha();

        // Testa vitória na diagonal principal
        jogo.fazerJogada(0, 0, 'X');
        jogo.fazerJogada(1, 1, 'X');
        jogo.fazerJogada(2, 2, 'X');
        CHECK(jogo.verificarVitoria('X'));

        // Reinicia o jogo
        jogo = JogoDaVelha();

        // Testa vitória na diagonal secundária
        jogo.fazerJogada(0, 2, 'O');
        jogo.fazerJogada(1, 1, 'O');
        jogo.fazerJogada(2, 0, 'O');
        CHECK(jogo.verificarVitoria('O'));
    }

    SUBCASE("Teste tabuleiroCheio()") {
        // Preenche todo o tabuleiro sem que ocorra uma vitória
        jogo.fazerJogada(0, 0, 'X');
        jogo.fazerJogada(0, 1, 'O');
        jogo.fazerJogada(0, 2, 'X');
        jogo.fazerJogada(1, 0, 'O');
        jogo.fazerJogada(1, 1, 'X');
        jogo.fazerJogada(1, 2, 'O');
        jogo.fazerJogada(2, 0, 'X');
        jogo.fazerJogada(2, 1, 'O');
        jogo.fazerJogada(2, 2, 'X');

        CHECK(jogo.tabuleiroCheio());
    }
}
