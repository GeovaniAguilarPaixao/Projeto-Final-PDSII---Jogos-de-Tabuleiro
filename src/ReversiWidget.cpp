#include "ReversiWidget.hpp"
#include "SDLUtils.hpp"
#include <cmath>
#include <iostream>

ReversiWidget::ReversiWidget(SDL_Renderer* renderer)
    : renderer(renderer), larguraCelula(50), alturaCelula(50) {
    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    }

    // Substitua pelo caminho para a sua fonte
    fonte = TTF_OpenFont("./light-arial.ttf", 24);
    if (!fonte) {
        std::cerr << "Não foi possível carregar a fonte: " << TTF_GetError() << std::endl;
    }
}

ReversiWidget::~ReversiWidget() {
    TTF_CloseFont(fonte);
    TTF_Quit();
}

void ReversiWidget::desenhar() {
    desenharTabuleiro();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] != '-') {
                desenharJogada(i, j, tabuleiro[i][j]);
            }
        }
    }
}

void ReversiWidget::tratarEvento(SDL_Event& evento, char& jogadorAtual) {
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        int x = evento.button.x;
        int y = evento.button.y;

        int linha = y / alturaCelula;
        int coluna = x / larguraCelula;

        if (jogadaValida(linha, coluna, jogadorAtual)) {
            fazerJogada(linha, coluna, jogadorAtual);
            jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        }
    }
}

void ReversiWidget::desenharTabuleiro() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Desenha linhas verticais (colunas)
    for (int i = 0; i <= colunas; ++i) {
        SDL_RenderDrawLine(renderer, i * larguraCelula, 0, i * larguraCelula, linhas * alturaCelula);
    }

    // Desenha linhas horizontais (linhas)
    for (int i = 0; i <= linhas; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * alturaCelula, colunas * larguraCelula, i * alturaCelula);
    }
}

void ReversiWidget::desenharJogada(int linha, int coluna, char jogador) {
    SDL_Rect rect = {coluna * larguraCelula, linha * alturaCelula, larguraCelula, alturaCelula};
    int centerX = rect.x + rect.w / 2;
    int centerY = rect.y + rect.h / 2;
    int radius = std::min(rect.w, rect.h) / 3;

    // Desenha o contorno do círculo
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawCircle(renderer, centerX, centerY, radius);

    // Preenche o círculo com a cor correspondente
    if (jogador == 'X') {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Preenchimento preto
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Preenchimento branco
    }
    SDL_RenderFillCircle(renderer, centerX, centerY, radius - 2); // Preenchimento com pequeno offset
}

// Função auxiliar para desenhar um círculo preenchido
void ReversiWidget::SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Posição horizontal do pixel em relação ao centro
            int dy = radius - h; // Posição vertical do pixel em relação ao centro
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void ReversiWidget::exibirTexto(const std::string& texto, int x, int y) {
    SDL_Color cor = {0, 0, 0}; // Cor preta para o texto
    SDL_Surface* surface = TTF_RenderText_Solid(fonte, texto.c_str(), cor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void ReversiWidget::jogar() {
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
