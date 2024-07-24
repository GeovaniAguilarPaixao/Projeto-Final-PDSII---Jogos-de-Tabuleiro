#ifndef LIG4_HPP
#define LIG4_HPP

#include "JogoDeTabuleiro.hpp"

class Lig4 : public JogoDeTabuleiro {
public:
    Lig4();

    bool jogadaValida(int coluna) const override;
    void fazerJogada(int coluna, char jogador) override;
    bool verificarVitoria(char jogador) const override;
    bool tabuleiroCheio() const override;
    bool isBidimensional() const override { return false; }

private:
    bool dentroDoTabuleiro(int linha, int coluna) const;
    bool verificarDirecao(int linha, int coluna, int deltaLinha, int deltaColuna, char jogador) const;
};

#endif // LIG4_HPP
