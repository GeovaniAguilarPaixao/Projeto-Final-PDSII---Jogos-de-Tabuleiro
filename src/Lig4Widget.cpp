#include "Lig4Widget.hpp"
#include <iostream>

Lig4Widget::Lig4Widget(SDL_Renderer* renderer) : renderer(renderer), larguraCelula(100), alturaCelula(100) {}

Lig4Widget::~Lig4Widget() {}

void Lig4Widget::desenhar() {
    desenharTabuleiro();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] != '-') {
                desenharJogada(j, tabuleiro[i][j]);
            }
        }
    }
}

void Lig4Widget::tratarEvento(SDL_Event& evento, char& jogadorAtual) {
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        int coluna = evento.button.x / larguraCelula;
        if (jogadaValida(coluna)) {
            fazerJogada(coluna, jogadorAtual);
            jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        }
    }
}

void Lig4Widget::desenharTabuleiro() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < colunas; ++i) {
        SDL_RenderDrawLine(renderer, i * larguraCelula, 0, i * larguraCelula, linhas * alturaCelula);
    }
}

void Lig4Widget::desenharJogada(int coluna, char jogador) {
    for (int linha = linhas - 1; linha >= 0; --linha) {
        if (tabuleiro[linha][coluna] != '-') {
            SDL_Rect rect = {coluna * larguraCelula, linha * alturaCelula, larguraCelula, alturaCelula};
            if (jogador == 'X') {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            break;
        }
    }
}
