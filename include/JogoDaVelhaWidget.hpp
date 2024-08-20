#ifndef JOGO_DA_VELHA_WIDGET_HPP
#define JOGO_DA_VELHA_WIDGET_HPP

#include "JogoDaVelha.hpp"
#include "Jogada.hpp"
#include "MenuState.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <memory>

class JogoDaVelhaWidget : public JogoDaVelha {
public:
    JogoDaVelhaWidget(SDL_Renderer* renderer, TTF_Font* fonte, MenuState& menuState);
    ~JogoDaVelhaWidget();

    void desenhar();
    int jogar(const std::vector<std::shared_ptr<Jogador>>& jogadoresSelecionados);
    void tratarEvento(SDL_Event& evento, char& jogadorAtual);

private:
    SDL_Renderer* renderer;
    TTF_Font* fonte;
    int larguraCelula;
    int alturaCelula;
    MenuState& menuState;

    void desenharTabuleiro();
    void desenharJogada(int linha, int coluna, char jogador);
    void exibirTexto(const std::string& texto, int x, int y);
};

#endif // JOGO_DA_VELHA_WIDGET_HPP
