#ifndef LIG4_WIDGET_HPP
#define LIG4_WIDGET_HPP

#include "Lig4.hpp"
#include <SDL2/SDL.h>

class Lig4Widget : public Lig4 {
public:
    Lig4Widget(SDL_Renderer* renderer);
    ~Lig4Widget();

    void desenhar();
    void tratarEvento(SDL_Event& evento, char& jogadorAtual);

private:
    SDL_Renderer* renderer;
    int larguraCelula;
    int alturaCelula;
    void desenharTabuleiro();
    void desenharJogada(int coluna, char jogador);
};

#endif // LIG4_WIDGET_HPP
