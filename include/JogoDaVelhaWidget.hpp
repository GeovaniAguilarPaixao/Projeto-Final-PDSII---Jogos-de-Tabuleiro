#ifndef JOGO_DA_VELHA_WIDGET_HPP
#define JOGO_DA_VELHA_WIDGET_HPP

#include "JogoDaVelha.hpp"
#include <SDL2/SDL.h>

class JogoDaVelhaWidget : public JogoDaVelha {
public:
    JogoDaVelhaWidget(SDL_Renderer* renderer);
    ~JogoDaVelhaWidget();

    void desenhar();
    void tratarEvento(SDL_Event& evento, char& jogadorAtual);

private:
    SDL_Renderer* renderer;
    int larguraCelula;
    int alturaCelula;
    void desenharTabuleiro();
    void desenharJogada(int linha, int coluna, char jogador);
};

#endif // JOGO_DA_VELHA_WIDGET_HPP
