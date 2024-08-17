#include "Lig4Widget.hpp"
#include "SDLUtils.hpp"
#include <iostream>

Lig4Widget::Lig4Widget(SDL_Renderer* renderer, TTF_Font* fonte)  
    : renderer(renderer), fonte(fonte), larguraCelula(70), alturaCelula(70) {
    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    }
    if (!fonte) {
        std::cerr << "Não foi possível carregar a fonte: " << TTF_GetError() << std::endl;
    }
}

Lig4Widget::~Lig4Widget() {
    TTF_CloseFont(fonte);
    TTF_Quit();
}

void Lig4Widget::desenhar() {
    desenharTabuleiro();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] != '-') {
                desenharJogada(i, j, tabuleiro[i][j]);
            }
        }
    }
}

void Lig4Widget::tratarEvento(SDL_Event& evento, char& jogadorAtual) {
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        int x = evento.button.x;

        int coluna = x / larguraCelula;
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

void Lig4Widget::desenharJogada(int linha, int coluna, char jogador) {
    SDL_Rect rect = {coluna * larguraCelula, linha * alturaCelula, larguraCelula, alturaCelula};
    int centerX = rect.x + rect.w / 2;
    int centerY = rect.y + rect.h / 2;
    int radius = std::min(rect.w, rect.h) / 3;

    if (jogador == 'X') {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Jogador 1 - círculo vermelho
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Jogador 2 - círculo azul
    }
    SDL_RenderDrawCircle(renderer, centerX, centerY, radius);
}

void Lig4Widget::exibirTexto(const std::string& texto, int x, int y) {
    SDL_Color cor = {0, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(fonte, texto.c_str(), cor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Lig4Widget::fazerJogada(int coluna, char jogador) {
    for (int linha = linhas - 1; linha >= 0; --linha) {
        if (tabuleiro[linha][coluna] == '-') {
            tabuleiro[linha][coluna] = jogador;
            break;
        }
    }
}

bool Lig4Widget::jogadaValida(int coluna) {
    return tabuleiro[0][coluna] == '-';
}

void Lig4Widget::jogar() {
    bool quit = false;
    SDL_Event e;
    char jogadorAtual = 'X';

    // Obtém a largura da janela
    int larguraJanela;
    SDL_GetRendererOutputSize(renderer, &larguraJanela, nullptr);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                tratarEvento(e, jogadorAtual);
            }
        }

        desenhar();

        // Exibe o jogador atual na parte superior direita da janela
        std::string textoJogador = (jogadorAtual == 'X') ? "Jogador 1 (O)" : "Jogador 2 (X)";
        int xTexto = larguraJanela - 10 - textoJogador.size() * 10; // Ajusta a posição X com base no comprimento do texto
        exibirTexto(textoJogador, xTexto, 10); // Ajusta a posição Y conforme necessário

        SDL_RenderPresent(renderer);

        if (verificarVitoria(jogadorAtual) || tabuleiroCheio()) {
            quit = true;
        }
    }
}
