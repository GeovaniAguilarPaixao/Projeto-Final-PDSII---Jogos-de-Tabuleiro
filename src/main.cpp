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

enum Menu { MENU_PRINCIPAL, MENU_JOGADORES, MENU_JOGOS, MENU_ADICIONAR_JOGADOR, MENU_LISTAR_JOGADORES };
enum JogoSelecionado { NONE, JOGO_DA_VELHA, LIG4, REVERSI };

// Função para renderizar o texto ao lado dos botões
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = { 0, 0, 0, 255 };  // Cor preta
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Função para renderizar o menu principal
void renderMenuPrincipal(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect botaoJogadores, SDL_Rect botaoJogos, SDL_Rect botaoSair) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); // Azul
    SDL_RenderFillRect(renderer, &botaoJogadores);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // Verde
    SDL_RenderFillRect(renderer, &botaoJogos);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Vermelho
    SDL_RenderFillRect(renderer, &botaoSair);

    renderText(renderer, font, "Jogadores", botaoJogadores.x + botaoJogadores.w + 10, botaoJogadores.y + 10);
    renderText(renderer, font, "Jogos", botaoJogos.x + botaoJogos.w + 10, botaoJogos.y + 10);
    renderText(renderer, font, "Sair", botaoSair.x + botaoSair.w + 10, botaoSair.y + 10);

    SDL_RenderPresent(renderer);
}

// Função para renderizar o menu de jogadores
void renderMenuJogadores(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect botaoAdicionar, SDL_Rect botaoListar, SDL_Rect botaoVoltar) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); // Azul
    SDL_RenderFillRect(renderer, &botaoAdicionar);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // Verde
    SDL_RenderFillRect(renderer, &botaoListar);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF); // Laranja
    SDL_RenderFillRect(renderer, &botaoVoltar);

    renderText(renderer, font, "Adicionar Jogador", botaoAdicionar.x + botaoAdicionar.w + 10, botaoAdicionar.y + 10);
    renderText(renderer, font, "Listar Jogadores", botaoListar.x + botaoListar.w + 10, botaoListar.y + 10);
    renderText(renderer, font, "Voltar", botaoVoltar.x + botaoVoltar.w + 10, botaoVoltar.y + 10);

    SDL_RenderPresent(renderer);
}

// Função para renderizar o menu de jogos
void renderMenuJogos(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect botaoJogoDaVelha, SDL_Rect botaoLig4, SDL_Rect botaoReversi, SDL_Rect botaoVoltar) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); // Azul
    SDL_RenderFillRect(renderer, &botaoJogoDaVelha);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Vermelho
    SDL_RenderFillRect(renderer, &botaoLig4);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // Verde
    SDL_RenderFillRect(renderer, &botaoReversi);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF); // Laranja
    SDL_RenderFillRect(renderer, &botaoVoltar);

    renderText(renderer, font, "Jogo da Velha", botaoJogoDaVelha.x + botaoJogoDaVelha.w + 10, botaoJogoDaVelha.y + 10);
    renderText(renderer, font, "Lig4", botaoLig4.x + botaoLig4.w + 10, botaoLig4.y + 10);
    renderText(renderer, font, "Reversi", botaoReversi.x + botaoReversi.w + 10, botaoReversi.y + 10);
    renderText(renderer, font, "Voltar", botaoVoltar.x + botaoVoltar.w + 10, botaoVoltar.y + 10);

    SDL_RenderPresent(renderer);
}

// Função para exibir um alerta ao usuário
void exibirAlerta(SDL_Renderer* renderer, TTF_Font* font, const std::string& mensagem) {
    SDL_Color color = {255, 0, 0, 255}; // Vermelho

try{
        SDL_Surface* surface = TTF_RenderText_Solid(font, mensagem.c_str(), color);
    if(!surface){
        throw std::runtime_error("Não foi possível criar superfície de texto." + std::string(TTF_GetError()));
    }
    
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture){
        SDL_FreeSurface(surface);
        throw std::runtime_error("Não foi possível criar textura" + std::string(SDL_GetError()));)
    }
        SDL_Rect dstRect = {100, 400, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_RenderPresent(renderer);
    
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    
        SDL_Delay(2000); // Espera 2 segundos antes de continuar
    }
    catch(const std::exception& e){
        SDL_Log("Erro: %s", e.what());
        SDL_Quit();
        return -1;
    }
}

int main(int argc, char* args[]) {
try{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Não foi possível iniciar a SDL: "+std::string(SDL_GetError()));
       
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error("Não foi possível iniciar a TTF: "+ std::string(TTF_GetError()));
       
    }
}
catch(const std::excepcion& e){
    SDL_log("Erro: %s", e.what());
    SDL_Quit();
}

try{    
        SDL_Window* window = SDL_CreateWindow("Menu de Jogos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window){
        throw std:runtime_error("Falha ao criar a janela."+std::string(SDL_GetError()));
    }
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        throw std:runtime_error("Falha ao criar o renderizador."+std::string(SDL_GetError()));
    }
    TTF_Font* font = TTF_OpenFont("./light-arial.ttf", 24);
    if(!font){
        throw std::runtime_error("Falha ao carregar a fonte."+std::string(SDL_GetError()));
    }  

}
    catch(const std::exception& e){
        SLD_Log("Erro ao inicializar o jogo: %s", e.what());
        SDL_Quit();
        return -1;
    }

    SDL_Rect botaoJogadores = {100, 100, 60, 60};
    SDL_Rect botaoJogos = {100, 200, 60, 60};
    SDL_Rect botaoSair = {100, 300, 60, 60};
    SDL_Rect botaoAdicionar = {100, 100, 200, 50};
    SDL_Rect botaoListar = {100, 200, 200, 50};
    SDL_Rect botaoVoltar = {100, 300, 200, 50};
    SDL_Rect botaoJogoDaVelha = {100, 100, 60, 60};
    SDL_Rect botaoLig4 = {100, 200, 60, 60};
    SDL_Rect botaoReversi = {100, 300, 60, 60};
    SDL_Rect botaoConfirmar = {400, 100, 200, 50};

    bool quit = false;
    SDL_Event e;
    Menu menuAtual = MENU_PRINCIPAL;
    JogoSelecionado jogoSelecionado = NONE;
    JogadaWidget jogadaWidget(renderer, font, "./data/");
    std::string jogadorSelecionado1, jogadorSelecionado2;
    bool jogador1Selecionado = false, jogador2Selecionado = false;

    SDL_StartTextInput();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            switch (menuAtual) {
                case MENU_PRINCIPAL:
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        SDL_Point ponto = {x, y};

                        if (SDL_PointInRect(&ponto, &botaoJogadores)) {
                            menuAtual = MENU_JOGADORES;
                        } else if (SDL_PointInRect(&ponto, &botaoJogos)) {
                            menuAtual = MENU_JOGOS;
                        } else if (SDL_PointInRect(&ponto, &botaoSair)) {
                            quit = true;
                        }
                    }
                    break;

                case MENU_JOGADORES:
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        SDL_Point ponto = {x, y};

                        if (SDL_PointInRect(&ponto, &botaoAdicionar)) {
                            menuAtual = MENU_ADICIONAR_JOGADOR;
                        } else if (SDL_PointInRect(&ponto, &botaoListar)) {
                            menuAtual = MENU_LISTAR_JOGADORES;
                        } else if (SDL_PointInRect(&ponto, &botaoVoltar)) {
                            menuAtual = MENU_PRINCIPAL;
                        }
                    }
                    break;

                case MENU_ADICIONAR_JOGADOR:
                    jogadaWidget.tratarEvento(e);
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        SDL_Point ponto = {x, y};

                        if (SDL_PointInRect(&ponto, &botaoConfirmar)) {
                            if (jogadaWidget.getApelido().empty() || jogadaWidget.getNome().empty()) {
                                exibirAlerta(renderer, font, "Por favor, preencha todos os campos!");
                            } else {
                                jogadaWidget.salvarJogador();
                                menuAtual = MENU_JOGADORES;
                            }
                        } else if (SDL_PointInRect(&ponto, &botaoVoltar)) {
                            menuAtual = MENU_JOGADORES;
                        }
                    }
                    jogadaWidget.desenhar();
                    break;

                case MENU_LISTAR_JOGADORES:
                    jogadaWidget.tratarEvento(e);
                    // Implementar lógica de seleção de jogadores, remoção e validação aqui
                    // ...

                    if (jogador1Selecionado && jogador2Selecionado) {
                        menuAtual = MENU_JOGADORES;
                    }
                    break;

                case MENU_JOGOS:
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        SDL_Point ponto = {x, y};

                        if (SDL_PointInRect(&ponto, &botaoJogoDaVelha)) {
                            jogoSelecionado = JOGO_DA_VELHA;
                        } else if (SDL_PointInRect(&ponto, &botaoLig4)) {
                            jogoSelecionado = LIG4;
                        } else if (SDL_PointInRect(&ponto, &botaoReversi)) {
                            jogoSelecionado = REVERSI;
                        } else if (SDL_PointInRect(&ponto, &botaoVoltar)) {
                            menuAtual = MENU_PRINCIPAL;
                        }

                        if (jogoSelecionado != NONE && jogador1Selecionado && jogador2Selecionado) {
                            // Carregar o jogo com os jogadores selecionados
                            // Implementar lógica para iniciar o jogo aqui
                            // ...
                            menuAtual = MENU_PRINCIPAL;  // Retornar ao menu principal após o jogo
                        }
                    }
                    break;
            }
        }

        // Renderização dos menus
        switch (menuAtual) {
            case MENU_PRINCIPAL:
                renderMenuPrincipal(renderer, font, botaoJogadores, botaoJogos, botaoSair);
                break;
            case MENU_JOGADORES:
                renderMenuJogadores(renderer, font, botaoAdicionar, botaoListar, botaoVoltar);
                break;
            case MENU_JOGOS:
                renderMenuJogos(renderer, font, botaoJogoDaVelha, botaoLig4, botaoReversi, botaoVoltar);
                break;
        }
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
