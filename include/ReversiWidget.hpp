#ifndef REVERSI_WIDGET_HPP
#define REVERSI_WIDGET_HPP

#include "Reversi.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class ReversiWidget : public Reversi {
public:
    ReversiWidget(SDL_Renderer* renderer, TTF_Font* fonte);
    ~ReversiWidget();

    void desenhar();
    void jogar();
    void tratarEvento(SDL_Event& evento, char& jogadorAtual);

private:
    SDL_Renderer* renderer;
    TTF_Font* fonte;
    int larguraCelula;
    int alturaCelula;

    void desenharTabuleiro();
    void desenharJogada(int linha, int coluna, char jogador);
    void exibirTexto(const std::string& texto, int x, int y);

    void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius); 
};

#endif // REVERSI_WIDGET_HPP
