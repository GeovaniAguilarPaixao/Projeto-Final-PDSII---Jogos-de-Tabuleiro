#include "JogoDaVelhaWidget.hpp"
#include "SDLUtils.hpp"
#include <iostream>

JogoDaVelhaWidget::JogoDaVelhaWidget(SDL_Renderer* renderer) 
    : renderer(renderer), larguraCelula(100), alturaCelula(100) {
    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    }
    fonte = TTF_OpenFont("./light-arial.ttf", 24);
    // Substitua pelo caminho para a sua fonte
    if (!fonte) {
        std::cerr << "Não foi possível carregar a fonte: " << TTF_GetError() << std::endl;
    }
}

JogoDaVelhaWidget::~JogoDaVelhaWidget() {
    TTF_CloseFont(fonte);
    TTF_Quit();
}

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
    int centerX = rect.x + rect.w / 2;
    int centerY = rect.y + rect.h / 2;
    int radius = std::min(rect.w, rect.h) / 3;

    if (jogador == 'X') {
        // Desenha um "X" vermelho
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x, rect.y + rect.h);
    } else {
        // Desenha um círculo azul
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawCircle(renderer, centerX, centerY, radius);
    }
}

void JogoDaVelhaWidget::exibirTexto(const std::string& texto, int x, int y) {
    SDL_Color cor = {0, 0, 0}; // Cor preta para o texto
    SDL_Surface* surface = TTF_RenderText_Solid(fonte, texto.c_str(), cor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void JogoDaVelhaWidget::jogar() {
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
        std::string textoJogador = (jogadorAtual == 'X') ? "Jogador 1 (X)" : "Jogador 2 (O)";
        int xTexto = larguraJanela - 10 - textoJogador.size() * 10; // Ajuste a posição X com base no comprimento do texto
        exibirTexto(textoJogador, xTexto, 10); // Ajuste a posição Y conforme necessário

        SDL_RenderPresent(renderer);

        if (verificarVitoria(jogadorAtual) || tabuleiroCheio()) {
            quit = true;
        }
    }
}
