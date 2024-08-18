/*#include <iostream>
#include <fstream>
#include <map>
#include "Reversi.hpp"
#include "Lig4.hpp"
#include "JogoDaVelha.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"

void jogar(JogoDeTabuleiro* jogo) {
    char jogador = 'X';
    while (!jogo->tabuleiroCheio()) {
        jogo->imprimirTabuleiro();

        int linha = -1, coluna = -1;
        if (jogo->isBidimensional()) {
            // Para jogos bidimensionais
            std::cout << "Turno do jogador " << jogador << " (linha coluna): ";
            std::cin >> linha >> coluna;
            linha -= 1; // Ajuste para o índice da linha
            coluna -= 1; // Ajuste para o índice da coluna
            if (jogo->jogadaValida(linha, coluna)) {
                bool verificaJogada = jogo->fazerJogada(linha, coluna, jogador);
                if(!verificaJogada){
                    jogador = (jogador == 'X') ? 'O' : 'X';
                }
            } else {
                std::cout << "Jogada inválida. Tente novamente.\n";
                continue;
            }

        } else {
            // Para jogos unidimensionais
            std::cout << "Turno do jogador " << jogador << " (coluna): ";
            std::cin >> coluna;
            coluna -= 1; // Ajuste para o índice da coluna  
            if (jogo->jogadaValida(coluna)) {
                jogo->fazerJogada(coluna, jogador);
            } else {
                std::cout << "Jogada inválida. Tente novamente.\n";
                continue;
            }

        }

        if (jogo->verificarVitoria(jogador)) {
            jogo->imprimirTabuleiro();
            std::cout << "Jogador " << jogador << " venceu!\n";
            return;
        }

        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    jogo->imprimirTabuleiro();
    std::cout << "Empate!\n";
}

int main() {
    // ----- TESTES DA CLASSE JOGADA ------
    // ----- MANTER COMO COMENTÁRIO ------
    // std::string data_path;
    // data_path = "data";
    // std::unique_ptr<Jogada> jogada = std::make_unique<Jogada>();
    // jogada->carregarJogadores(data_path);
    // jogada->listarJogadores();
    // jogada->adicionarJogador("Jogador1","Jogador 1");
    // jogada->adicionarJogador("Jogador2","Jogador 2");
    // jogada->adicionarJogador("Jogador3", "Jogador 3");
    // jogada->listarJogadores();
    // jogada->removerJogador("Jogador3", "Jogador 3");
    // jogada->listarJogadores();
    // jogada->adicionarJogador("Jogador4", "Jogador 4");
    // jogada->listarJogadores();
    // jogada->salvarJogadores(data_path);
    // jogada->removerJogador("Jogador4",data_path);
    // jogada->listarJogadores();

    int escolha = -1;
    char modo;
    JogoDeTabuleiro* jogo = nullptr;

    while (true) {
        while (true) {
            std::cout << "Escolha o jogo:\n1. Reversi\n2. Lig4\n3. JogoDaVelha\n4. Sair\n";
            std::cin >> escolha;

            if (escolha == 1) {
                jogo = new Reversi();
                break;
            } else if (escolha == 2) {
                jogo = new Lig4();
                break;
            } else if (escolha == 3) {
                jogo = new JogoDaVelha();
                break;
            } else if (escolha == 4) {
                break;
            } else {
                std::cout << "Escolha inválida.\n";
            }
        }

        if (escolha == 4)
            break;

        if (escolha == 3) { // Jogo da Velha
            std::cout << "Deseja jogar contra outro jogador ou contra a IA? (P/I): ";
            std::cin >> modo;
        }

        char jogador = 'X';
        while (!jogo->tabuleiroCheio()) {
            jogo->imprimirTabuleiro();

            int linha = -1, coluna = -1;

            if (modo == 'I' && jogador == 'O') {
                dynamic_cast<JogoDaVelha*>(jogo)->jogadaIA(jogador);  // IA faz a jogada
            } else {
                std::cout << "Turno do jogador " << jogador << " (linha coluna): ";
                std::cin >> linha >> coluna;
                linha -= 1;
                coluna -= 1;

                if (jogo->jogadaValida(linha, coluna)) {
                    jogo->fazerJogada(linha, coluna, jogador);
                } else {
                    std::cout << "Jogada inválida. Tente novamente.\n";
                    continue;
                }
            }

            if (jogo->verificarVitoria(jogador)) {
                jogo->imprimirTabuleiro();
                std::cout << "Jogador " << jogador << " venceu!\n";
                break;
            }

            jogador = (jogador == 'X') ? 'O' : 'X';
        }

        if (!jogo->verificarVitoria('X') && !jogo->verificarVitoria('O')) {
            jogo->imprimirTabuleiro();
            std::cout << "Empate!\n";
        }

        delete jogo;
    }
    
    return 0;
}*/

//Teste Main SDL

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "JogoDaVelhaWidget.hpp"
#include "Lig4Widget.hpp"
#include "ReversiWidget.hpp"
#include "JogadaWidget.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum JogoSelecionado { NONE, JOGO_DA_VELHA, LIG4, REVERSI, JOGADA };

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect botaoJogoDaVelha, SDL_Rect botaoLig4, SDL_Rect botaoReversi, SDL_Rect botaoJogada, SDL_Rect botaoSair, SDL_Point mousePos) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    auto renderButton = [&](SDL_Rect botao, const char* text, SDL_Color color, SDL_Color hoverColor){
        if(SDL_PointInRect(&mousePos, &botao)){
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        }else{
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        }
        SDL_RenderFillRect(renderer, &botao);
        renderText(renderer, font, text, botao.x + botao.w / 2, botao.y + botao.h / 2);
    };

    renderButton(botaoJogoDaVelha, "Jogo da Velha", { 0x00, 0x00, 0xFF, 0xFF }, { 0x00, 0x00, 0xAA, 0xFF });
    renderButton(botaoLig4, "Lig4", { 0xFF, 0x00, 0x00, 0xFF }, { 0xAA, 0x00, 0x00, 0xFF });
    renderButton(botaoReversi, "Reversi", { 0x00, 0xFF, 0x00, 0xFF }, { 0x00, 0xAA, 0x00, 0xFF });
    renderButton(botaoJogada, "Jogadores", { 0xFF, 0xA5, 0x00, 0xFF }, { 0xAA, 0x69, 0x00, 0xFF });
    renderButton(botaoSair, "Sair", { 0x80, 0x00, 0x80, 0xFF }, { 0x60, 0x00, 0x60, 0xFF });

    
//    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
//    SDL_RenderFillRect(renderer, &botaoJogoDaVelha);

//    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
//    SDL_RenderFillRect(renderer, &botaoLig4);

//    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
//    SDL_RenderFillRect(renderer, &botaoReversi);

//    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF); // Cor diferente para o botão de Jogadores
//    SDL_RenderFillRect(renderer, &botaoJogada);

//    SDL_SetRenderDrawColor(renderer, 0x80, 0x00, 0x80, 0xFF); // Cor diferente para o botão de Sair
//    SDL_RenderFillRect(renderer, &botaoSair);

//    renderText(renderer, font, "Jogo da Velha", botaoJogoDaVelha.x + 10, botaoJogoDaVelha.y + 10);
//    renderText(renderer, font, "Lig4", botaoLig4.x + 10, botaoLig4.y + 10);
//    renderText(renderer, font, "Reversi", botaoReversi.x + 10, botaoReversi.y + 10);
//    renderText(renderer, font, "Jogadores", botaoJogada.x + 10, botaoJogada.y + 10);
//    renderText(renderer, font, "Sair", botaoSair.x + 10, botaoSair.y + 10);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("light-arial.ttf", 24);
    if (!font) {
        std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Rect botaoJogoDaVelha = { 50, 50, 200, 50 };
    SDL_Rect botaoLig4 = { 50, 150, 200, 50 };
    SDL_Rect botaoReversi = { 50, 250, 200, 50 };
    SDL_Rect botaoJogada = { 50, 350, 200, 50 };
    SDL_Rect botaoSair = { 50, 450, 200, 50 };

    JogoSelecionado jogoAtual = NONE;
    bool sair = false;
    SDL_Event e;

    JogoDaVelhaWidget jogoDaVelha(renderer, font);
    Lig4Widget lig4(renderer, font);
    ReversiWidget reversi(renderer, font);
    JogadaWidget jogadaWidget(renderer, font, "data");

    SDL_Point mousePos;
    
    while (!sair) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                sair = true;
            } else if (e.type == SDL_MOUSEMOTION) {
                
                SDL_GetMouseState(&mousePos.x, &mousePos.
                    y);
            }else if(e.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                // Corrigido: usar variáveis temporárias para os pontos
                //SDL_Point pontoClique = {x, y};

                if (SDL_PointInRect(&mousePos, &botaoJogoDaVelha)) {
                    jogoAtual = JOGO_DA_VELHA;
                } else if (SDL_PointInRect(&mousePos, &botaoLig4)) {
                    jogoAtual = LIG4;
                } else if (SDL_PointInRect(&mousePos, &botaoReversi)) {
                    jogoAtual = REVERSI;
                } else if (SDL_PointInRect(&mousePos, &botaoJogada)) {
                    jogoAtual = JOGADA;
                } else if (SDL_PointInRect(&mousePos, &botaoSair)) {
                    sair = true;
                }
            }
        }

        switch (jogoAtual) {
            case JOGO_DA_VELHA:
                jogoDaVelha.desenhar();
                break;
            case LIG4:
                lig4.desenhar();
                break;
            case REVERSI:
                reversi.desenhar();
                break;
            case JOGADA:
                jogadaWidget.desenhar();
                break;
            default:
                renderMenu(renderer, font, botaoJogoDaVelha, botaoLig4, botaoReversi, botaoJogada, botaoSair, mousePos);
                break;
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
