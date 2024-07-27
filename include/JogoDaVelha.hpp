#ifndef JOGO_DA_VELHA_HPP
#define JOGO_DA_VELHA_HPP

#include "JogoDeTabuleiro.hpp"

class JogoDaVelha : public JogoDeTabuleiro {
public:
    JogoDaVelha();
    ~JogoDaVelha() = default;

    bool verificarVitoria(char jogador) const override;
    bool tabuleiroCheio() const override;
    bool isBidimensional() const override { return true; }
};

#endif // JOGO_DA_VELHA_HPP
