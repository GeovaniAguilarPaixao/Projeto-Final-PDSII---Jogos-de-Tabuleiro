#ifndef REVERSI_WIDGET_HPP
#define REVERSI_WIDGET_HPP

#include "Reversi.hpp"
#include "Jogada.hpp"
#include "MenuState.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <memory>

class ReversiWidget : public Reversi {
public:
    ReversiWidget(SDL_Renderer* renderer, TTF_Font* fonte, MenuState& menuState);
    ~ReversiWidget();

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

    void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius); 
};

#endif // REVERSI_WIDGET_HPP
