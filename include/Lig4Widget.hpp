#ifndef LIG4_WIDGET_HPP
#define LIG4_WIDGET_HPP

#include "Lig4.hpp"
#include "Jogada.hpp"
#include "MenuState.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <memory>

class Lig4Widget : public Lig4 {
public:
    Lig4Widget(SDL_Renderer* renderer, TTF_Font* fonte, MenuState& menuState);
    ~Lig4Widget();

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
    void fazerJogada(int coluna, char jogador);
    bool jogadaValida(int coluna);
};

#endif // LIG4_WIDGET_HPP
