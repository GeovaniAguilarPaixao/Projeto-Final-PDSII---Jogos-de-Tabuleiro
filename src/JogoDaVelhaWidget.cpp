#include "JogoDaVelhaWidget.hpp"
#include <iostream>

JogoDaVelhaWidget::JogoDaVelhaWidget(SDL_Renderer* renderer) : renderer(renderer), larguraCelula(100), alturaCelula(100) {}

JogoDaVelhaWidget::~JogoDaVelhaWidget() {}

void JogoDaVelhaWidget::desenhar() {
    desenharTabuleiro();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] != '-') {
                desenharJogada(i, j, tabuleiro[i][j]);
            }
        }
    }
}

void JogoDaVelhaWidget::tratarEvento(SDL_Event& evento, char& jogadorAtual) {
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        int x = evento.button.x;
        int y = evento.button.y;

        int linha = y / alturaCelula;
        int coluna = x / larguraCelula;

        if (jogadaValida(linha, coluna)) {
            fazerJogada(linha, coluna, jogadorAtual);
            jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        }
    }
}

void JogoDaVelhaWidget::desenharTabuleiro() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < linhas; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * alturaCelula, colunas * larguraCelula, i * alturaCelula);
        SDL_RenderDrawLine(renderer, i * larguraCelula, 0, i * larguraCelula, linhas * alturaCelula);
    }
}

void JogoDaVelhaWidget::desenharJogada(int linha, int coluna, char jogador) {
    SDL_Rect rect = {coluna * larguraCelula, linha * alturaCelula, larguraCelula, alturaCelula};
    if (jogador == 'X') {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    }
    SDL_RenderFillRect(renderer, &rect);
}
