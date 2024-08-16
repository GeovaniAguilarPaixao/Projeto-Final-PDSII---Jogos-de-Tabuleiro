#include <iostream>
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
}

/*Teste Main SDL

#include <SDL2/SDL.h>
#include <iostream>
#include "JogoDaVelhaWidget.hpp"
#include "Lig4Widget.hpp"
#include "ReversiWidget.hpp"

// Constantes para as dimensões da janela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum JogoSelecionado { NONE, JOGO_DA_VELHA, LIG4, REVERSI };

void renderMenu(SDL_Renderer* renderer, SDL_Rect botaoJogoDaVelha, SDL_Rect botaoLig4, SDL_Rect botaoReversi) {
    // Cor de fundo
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Cor dos botões
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);

    // Renderizar os botões
    SDL_RenderFillRect(renderer, &botaoJogoDaVelha);
    SDL_RenderFillRect(renderer, &botaoLig4);
    SDL_RenderFillRect(renderer, &botaoReversi);

    // Renderizar o que foi preparado
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
    // Inicialização da SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Não foi possível inicializar SDL: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Menu de Jogos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        SDL_Log("Não foi possível criar janela ou renderizador: %s", SDL_GetError());
        return -1;
    }

    // Definir os botões para os jogos
    SDL_Rect botaoJogoDaVelha = { 200, 100, 240, 60 };
    SDL_Rect botaoLig4 = { 200, 200, 240, 60 };
    SDL_Rect botaoReversi = { 200, 300, 240, 60 };

    bool quit = false;
    SDL_Event e;
    JogoSelecionado jogoSelecionado = NONE;

    while (!quit) {
        // Renderizar o menu
        renderMenu(renderer, botaoJogoDaVelha, botaoLig4, botaoReversi);

        // Loop de eventos
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (SDL_PointInRect(&SDL_Point{x, y}, &botaoJogoDaVelha)) {
                    jogoSelecionado = JOGO_DA_VELHA;
                } else if (SDL_PointInRect(&SDL_Point{x, y}, &botaoLig4)) {
                    jogoSelecionado = LIG4;
                } else if (SDL_PointInRect(&SDL_Point{x, y}, &botaoReversi)) {
                    jogoSelecionado = REVERSI;
                }

                if (jogoSelecionado != NONE) {
                    break;
                }
            }
        }

        // Iniciar o jogo selecionado
        if (jogoSelecionado != NONE) {
            JogoDeTabuleiro* jogo = nullptr;
            if (jogoSelecionado == JOGO_DA_VELHA) {
                JogoDaVelhaWidget jogoDaVelhaWidget(renderer);
                jogo = &jogoDaVelhaWidget;
            } else if (jogoSelecionado == LIG4) {
                Lig4Widget lig4Widget(renderer);
                jogo = &lig4Widget;
            } else if (jogoSelecionado == REVERSI) {
                ReversiWidget reversiWidget(renderer);
                jogo = &reversiWidget;
            }

            if (jogo) {
                jogo->jogar();  // Implementar a lógica de jogar no widget
            }

            jogoSelecionado = NONE;  // Voltar ao menu após o término do jogo
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/
