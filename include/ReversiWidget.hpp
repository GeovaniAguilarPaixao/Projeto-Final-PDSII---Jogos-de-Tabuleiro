#ifndef REVERSI_WIDGET_HPP
#define REVERSI_WIDGET_HPP

#include "Reversi.hpp"
#include <SDL2/SDL.h>

class ReversiWidget : public Reversi {
public:
    ReversiWidget(SDL_Renderer* renderer);
    ~ReversiWidget();

    void desenhar();
    void tratarEvento(SDL_Event& evento, char& jogadorAtual);

private:
    SDL_Renderer* renderer;
    int larguraCelula;
    int alturaCelula;
    void desenharTabuleiro();
    void desenharJogada(int linha, int coluna, char jogador);
};

#endif // REVERSI_WIDGET_HPP
