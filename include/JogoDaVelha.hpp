#ifndef JOGODAVELHA_HPP
#define JOGODAVELHA_HPP

#include "JogoDeTabuleiro.hpp"

class JogoDaVelha : public JogoDeTabuleiro {
public:
    JogoDaVelha();

    bool verificarVitoria(char jogador) const override;
    bool tabuleiroCheio() const override;
    bool isBidimensional() const override;

    void jogadaIA(char jogador);

private:
    int minimax(int profundidade, bool isMaximizing, char jogador);
    int avaliar() const;
};

#endif // JOGODAVELHA_HPP
