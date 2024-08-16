#ifndef JOGO_DA_VELHA_WIDGET_HPP
#define JOGO_DA_VELHA_WIDGET_HPP

#include "JogoDaVelha.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class JogoDaVelhaWidget : public JogoDaVelha {
public:
    JogoDaVelhaWidget(SDL_Renderer* renderer);
    ~JogoDaVelhaWidget();

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
};

#endif // JOGO_DA_VELHA_WIDGET_HPP
