#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <cstring> 
#include "JogoDaVelhaWidget.hpp"
#include "Lig4Widget.hpp"
#include "ReversiWidget.hpp"
#include "JogadaWidget.hpp"
#include "MenuState.hpp"

// Definindo a função renderButton para desenhar um retângulo colorido
void renderButton(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    if (font == nullptr) {
        throw std::runtime_error("Fonte não carregada.");
    }

    if (text == nullptr || std::strlen(text) == 0) {
        throw std::runtime_error("Texto vazio fornecido para renderização.");
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface || surface->w == 0) {  // Verifica se a surface foi criada e tem largura
        if (surface) {
            SDL_FreeSurface(surface);
        }
        throw std::runtime_error(std::string("Erro ao criar a surface do texto: ") + TTF_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Erro ao criar a textura do texto.");
    }

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderMainMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Rect buttonJogadores = { 100, 100, 150, 50 };
    SDL_Rect buttonJogos = { 100, 200, 150, 50 };
    SDL_Rect buttonSair = { 100, 300, 150, 50 };

    try {
        renderButton(renderer, buttonJogadores, { 255, 0, 0, 255 });
        renderText(renderer, font, "Jogadores", 110, 110, textColor);

        renderButton(renderer, buttonJogos, { 0, 255, 0, 255 });
        renderText(renderer, font, "Jogos", 110, 210, textColor);

        renderButton(renderer, buttonSair, { 0, 0, 255, 255 });
        renderText(renderer, font, "Sair", 110, 310, textColor);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro ao renderizar o menu principal: " << e.what() << std::endl;
    }
}

void renderJogadoresMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Rect buttonAddJogador = { 100, 100, 200, 50 };
    SDL_Rect buttonListarJogadores = { 100, 200, 200, 50 };
    SDL_Rect buttonVoltar = { 100, 300, 150, 50 };

    try {
        renderButton(renderer, buttonAddJogador, { 255, 165, 0, 255 });
        renderText(renderer, font, "Adicionar Jogador", 110, 110, textColor);

        renderButton(renderer, buttonListarJogadores, { 60, 179, 113, 255 });
        renderText(renderer, font, "Listar Jogadores", 110, 210, textColor);

        renderButton(renderer, buttonVoltar, { 255, 69, 0, 255 });
        renderText(renderer, font, "Voltar", 110, 310, textColor);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro ao renderizar o menu de jogadores: " << e.what() << std::endl;
    }
}

void renderJogosMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Rect buttonJogoDaVelha = { 100, 100, 150, 50 };
    SDL_Rect buttonLig4 = { 100, 200, 150, 50 };
    SDL_Rect buttonReversi = { 100, 300, 150, 50 };
    SDL_Rect buttonVoltar = { 100, 400, 150, 50 };

    try {
        renderButton(renderer, buttonJogoDaVelha, { 255, 215, 0, 255 });
        renderText(renderer, font, "Jogo da Velha", 110, 110, textColor);

        renderButton(renderer, buttonLig4, { 0, 255, 255, 255 });
        renderText(renderer, font, "Lig4", 110, 210, textColor);

        renderButton(renderer, buttonReversi, { 127, 255, 0, 255 });
        renderText(renderer, font, "Reversi", 110, 310, textColor);

        renderButton(renderer, buttonVoltar, { 255, 69, 0, 255 });
        renderText(renderer, font, "Voltar", 110, 410, textColor);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro ao renderizar o menu de jogos: " << e.what() << std::endl;
    }
}

int main(int argc, char* args[]) {
    try {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("Erro ao inicializar a SDL.");
        }

        if (TTF_Init() == -1) {
            throw std::runtime_error("Erro ao inicializar o TTF.");
        }

        SDL_Window* window = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            throw std::runtime_error("Erro ao criar a janela.");
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            SDL_DestroyWindow(window);
            throw std::runtime_error("Erro ao criar o renderizador.");
        }

        TTF_Font* font = TTF_OpenFont("light-arial.ttf", 24);
        if (font == nullptr) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error("Erro ao carregar a fonte.");
        }

        std::string dirData = "data";
        MenuState menuState = MAIN_MENU; // Defina o estado inicial do menu

        JogadaWidget jogadaWidget(renderer, font, dirData, menuState);

        bool quit = false;
        SDL_Event e;

        while (!quit) {
            try {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);

                        if (menuState == MAIN_MENU) {
                            if (x > 100 && x < 250 && y > 100 && y < 150) {
                                menuState = JOGADORES_MENU;
                            } else if (x > 100 && x < 250 && y > 200 && y < 250) {
                                menuState = JOGOS_MENU;
                            } else if (x > 100 && x < 250 && y > 300 && y < 350) {
                                quit = true;
                            }
                        } else if (menuState == JOGADORES_MENU) {
                            if (x > 100 && x < 300 && y > 100 && y < 150) {
                                menuState = ADD_JOGADOR;
                            } else if (x > 100 && x < 300 && y > 200 && y < 250) {
                                menuState = LIST_JOGADORES;
                            } else if (x > 100 && x < 250 && y > 300 && y < 350) {
                                menuState = MAIN_MENU;
                            }
                        } else if (menuState == JOGOS_MENU) {
                            if (x > 100 && x < 250 && y > 100 && y < 150) {
                                menuState = JOGO_DA_VELHA;
                            } else if (x > 100 && x < 250 && y > 200 && y < 250) {
                                menuState = LIG4;
                            } else if (x > 100 && x < 250 && y > 300 && y < 350) {
                                menuState = REVERSI;
                            } else if (x > 100 && x < 250 && y > 400 && y < 450) {
                                menuState = MAIN_MENU;
                            }
                        } else if (menuState == ADD_JOGADOR || menuState == LIST_JOGADORES) {
                            if (x > 100 && x < 250 && y > 400 && y < 450) {
                                menuState = JOGADORES_MENU;
                            }
                        }
                    }
                }

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                if (menuState == MAIN_MENU) {
                    renderMainMenu(renderer, font);
                } else if (menuState == JOGADORES_MENU) {
                    renderJogadoresMenu(renderer, font);
                } else if (menuState == ADD_JOGADOR) {
                    jogadaWidget.inputNomeViaConsole();
                } else if (menuState == LIST_JOGADORES) {
                    jogadaWidget.renderListarJogadores();
                } else if (menuState == JOGOS_MENU) {
                    renderJogosMenu(renderer, font);
                } else if (menuState == JOGO_DA_VELHA) {
                    JogoDaVelhaWidget jogoDaVelhaWidget(renderer, font, menuState);
                    const std::vector<std::shared_ptr<Jogador>>& jogadoresSelecionados = jogadaWidget.getJogadoresSelecionados();
                    int resultado = jogoDaVelhaWidget.jogar(jogadoresSelecionados);
                    if (resultado == 0) { // jogadoresSelecionados[0] venceu
                        jogadoresSelecionados[0]->setEstatistica("JogoDaVelha", 0);
                        jogadoresSelecionados[1]->setEstatistica("JogoDaVelha", 1);
                    } else if (resultado == 1) { // jogadoresSelecionados[1] venceu
                        jogadoresSelecionados[0]->setEstatistica("JogoDaVelha", 1);
                        jogadoresSelecionados[1]->setEstatistica("JogoDaVelha", 0);
                    } else if (resultado == 2) { // empate
                        jogadoresSelecionados[0]->setEstatistica("JogoDaVelha", 2);
                        jogadoresSelecionados[1]->setEstatistica("JogoDaVelha", 2);
                    }
                    menuState = JOGOS_MENU;
                } else if (menuState == LIG4) {
                    Lig4Widget lig4Widget(renderer, font, menuState);
                    const std::vector<std::shared_ptr<Jogador>>& jogadoresSelecionados = jogadaWidget.getJogadoresSelecionados();
                    int resultado = lig4Widget.jogar(jogadoresSelecionados);
                    if (resultado == 0) { // jogadoresSelecionados[0] venceu
                        jogadoresSelecionados[0]->setEstatistica("Lig4", 0);
                        jogadoresSelecionados[1]->setEstatistica("Lig4", 1);
                    } else if (resultado == 1) { // jogadoresSelecionados[1] venceu
                        jogadoresSelecionados[0]->setEstatistica("Lig4", 1);
                        jogadoresSelecionados[1]->setEstatistica("Lig4", 0);
                    } else if (resultado == 2) { // empate
                        jogadoresSelecionados[0]->setEstatistica("Lig4", 2);
                        jogadoresSelecionados[1]->setEstatistica("Lig4", 2);
                    }
                    menuState = JOGOS_MENU; 
                } else if (menuState == REVERSI) {
                    ReversiWidget reversiWidget(renderer, font, menuState);
                    const std::vector<std::shared_ptr<Jogador>>& jogadoresSelecionados = jogadaWidget.getJogadoresSelecionados();
                    int resultado = reversiWidget.jogar(jogadoresSelecionados);
                    if (resultado == 0) { // jogadoresSelecionados[0] venceu
                        jogadoresSelecionados[0]->setEstatistica("Reversi", 0);
                        jogadoresSelecionados[1]->setEstatistica("Reversi", 1);
                    } else if (resultado == 1) { // jogadoresSelecionados[1] venceu
                        jogadoresSelecionados[0]->setEstatistica("Reversi", 1);
                        jogadoresSelecionados[1]->setEstatistica("Reversi", 0);
                    } else if (resultado == 2) { // empate
                        jogadoresSelecionados[0]->setEstatistica("Reversi", 2);
                        jogadoresSelecionados[1]->setEstatistica("Reversi", 2);
                    }
                    menuState = JOGOS_MENU;
                }
                font = TTF_OpenFont("light-arial.ttf", 24);
                SDL_RenderPresent(renderer);
            } catch (const std::exception& e) {
                std::cerr << "Erro durante o loop principal: " << e.what() << std::endl;
                // Continue a execução do programa
            }
        }

        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();

    } catch (const std::runtime_error& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
