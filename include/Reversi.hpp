// Reversi.hpp

#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "JogoDeTabuleiro.hpp"

class Reversi : public JogoDeTabuleiro {
public:
    Reversi();

    bool jogadaValida(int linha, int coluna) const override;
    void fazerJogada(int linha, int coluna, char jogador) override;
    bool verificarVitoria(char jogador) const override;
    bool tabuleiroCheio() const override;
    bool isBidimensional() const override { return true; }

private:
    bool dentroDoTabuleiro(int linha, int coluna) const;
    bool podeVirar(int linha, int coluna, int deltaLinha, int deltaColuna, char jogador) const;
};

#endif // REVERSI_HPP
