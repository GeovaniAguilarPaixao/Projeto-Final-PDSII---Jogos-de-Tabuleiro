#include "doctest.h"
#include "JogoDeTabuleiro.hpp"

// Implementa uma classe derivada de JogoDeTabuleiro para executar o teste
class JogoDeTabuleiroTeste : public JogoDeTabuleiro {
public:
    JogoDeTabuleiroTeste(int linhas, int colunas) : JogoDeTabuleiro(linhas, colunas) {}

    bool verificarVitoria(char jogador) const override {
        // Implementação teste apenas para fins de teste
        return false;
    }

    bool tabuleiroCheio() const override {
        // Implementação teste apenas para fins de teste
        return false;
    }

    bool isBidimensional() const override {
        // Implementação teste apenas para fins de teste
        return true;
    }
};

TEST_CASE("Teste da classe JogoDeTabuleiro") {
    JogoDeTabuleiroTeste jogo(6, 7);

    SUBCASE("Teste imprimirTabuleiro()") {
        jogo.imprimirTabuleiro();
        // Verifica se nenhuma excessão é retornada na impressão do tabuleiro
        CHECK_NOTHROW(jogo.imprimirTabuleiro());
    }

    SUBCASE("Teste jogadaValida() para duas dimensões") {
        CHECK(jogo.jogadaValida(0, 0));  // Posição válida
        CHECK(!jogo.jogadaValida(6, 7)); // Posição fora dos limites do tabuleiro
    }

    SUBCASE("Teste fazerJogada() para duas dimensões") {
        CHECK(jogo.fazerJogada(0, 0, 'X'));  // Posição válida
        CHECK(!jogo.fazerJogada(6, 7, 'X')); // Posição fora do limite
        CHECK(!jogo.fazerJogada(0, 0, 'X')); // Posição já ocupada
    }

    SUBCASE("Teste jogadaValida() para uma dimensão") {
        jogo = JogoDeTabuleiroTeste(1, 7); // Inicia um jogo unidimensional
        CHECK(jogo.jogadaValida(0)); // Posição válida
        CHECK(!jogo.jogadaValida(7)); // Posição fora dos limites do tabuleiro
    }

    SUBCASE("Teste fazerJogada para uma dimensão") {
        jogo = JogoDeTabuleiroTeste(1, 7); // Inicia um jogo unidimensional
        CHECK_NOTHROW(jogo.fazerJogada(0, 'X')); // Verifica se a jogada não retorna nenhuma excessão
    }
}
