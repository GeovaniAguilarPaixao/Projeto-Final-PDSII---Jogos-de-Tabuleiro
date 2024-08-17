#ifndef LIG4_WIDGET_HPP
#define LIG4_WIDGET_HPP

#include "Lig4.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Lig4Widget : public Lig4 {
public:
    Lig4Widget(SDL_Renderer* renderer, TTF_Font* fonte);
    ~Lig4Widget();

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
    void fazerJogada(int coluna, char jogador);
    bool jogadaValida(int coluna);
};

#endif // LIG4_WIDGET_HPP
