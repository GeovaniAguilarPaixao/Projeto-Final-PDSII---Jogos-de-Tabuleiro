#include "JogadaWidget.hpp"
#include <iostream>

void JogadaWidget::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color color = {0, 0, 0, 255};  // Cor preta
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

JogadaWidget::JogadaWidget(SDL_Renderer* renderer, TTF_Font* font, const std::string& dirData)
    : renderer(renderer), font(font), dirData(dirData), inputApelido(""), inputNome(""), cursor(0), modoAdicionar(false) {
    carregarJogadores();
    caixaTexto = {50, 50, 200, 30};  // Define a posição e o tamanho da caixa de texto
}

JogadaWidget::~JogadaWidget() {
    salvarJogadores();
}

void JogadaWidget::carregarJogadores() {
    jogada.carregarJogadores(dirData);
}

void JogadaWidget::salvarJogadores() {
    jogada.salvarJogadores(dirData);
}

void JogadaWidget::adicionarJogador(const std::string& apelido, const std::string& nome) {
    jogada.adicionarJogador(apelido, nome);
}

void JogadaWidget::removerJogador(const std::string& apelido) {
    jogada.removerJogador(apelido, dirData);
}

void JogadaWidget::listarJogadores() {
    jogada.listarJogadores();
}

void JogadaWidget::desenhar() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fundo branco
    SDL_RenderClear(renderer);

    if (modoAdicionar) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Cor da caixa de texto
        SDL_RenderFillRect(renderer, &caixaTexto);

        renderText(renderer, font, "Apelido:", caixaTexto.x, caixaTexto.y - 30);
        renderText(renderer, font, inputApelido, caixaTexto.x + 5, caixaTexto.y + 5);

        renderText(renderer, font, "Nome:", caixaTexto.x, caixaTexto.y + 50);
        renderText(renderer, font, inputNome, caixaTexto.x + 5, caixaTexto.y + 55);

        // Botões de Salvar e Voltar
        SDL_Rect botaoSalvar = {caixaTexto.x, caixaTexto.y + 100, 80, 30};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde para Salvar
        SDL_RenderFillRect(renderer, &botaoSalvar);
        renderText(renderer, font, "Salvar", botaoSalvar.x + 10, botaoSalvar.y + 5);

        SDL_Rect botaoVoltar = {caixaTexto.x + 100, caixaTexto.y + 100, 80, 30};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Vermelho para Voltar
        SDL_RenderFillRect(renderer, &botaoVoltar);
        renderText(renderer, font, "Voltar", botaoVoltar.x + 10, botaoVoltar.y + 5);
    } else {
        int y = 50;
        const auto& jogadores = jogada.getJogadores();

        for (const auto& [apelido, jogador] : jogadores) {
            std::string texto = "Jogador: " + apelido + " - Nome: " + jogador->getNome();
            renderText(renderer, font, texto, 50, y);
            y += 30;
        }
    }

    SDL_RenderPresent(renderer);
}

void JogadaWidget::tratarEvento(SDL_Event& e) {
    if (modoAdicionar) {
        if (e.type == SDL_TEXTINPUT) {
            if (cursor == 0) {
                inputApelido += e.text.text;
            } else {
                inputNome += e.text.text;
            }
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_BACKSPACE) {
                if (cursor == 0 && !inputApelido.empty()) {
                    inputApelido.pop_back();
                } else if (cursor == 1 && !inputNome.empty()) {
                    inputNome.pop_back();
                }
            } else if (e.key.keysym.sym == SDLK_TAB) {
                cursor = (cursor + 1) % 2;  // Alterna entre apelido e nome
            }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Point ponto = {x, y};

            SDL_Rect botaoSalvar = {caixaTexto.x, caixaTexto.y + 100, 80, 30};
            SDL_Rect botaoVoltar = {caixaTexto.x + 100, caixaTexto.y + 100, 80, 30};

            if (SDL_PointInRect(&ponto, &botaoSalvar)) {
                if (!inputApelido.empty() && !inputNome.empty()) {
                    adicionarJogador(inputApelido, inputNome);
                    modoAdicionar = false;
                    inputApelido.clear();
                    inputNome.clear();
                } else {
                    std::cout << "Preencha todos os campos!" << std::endl;
                }
            } else if (SDL_PointInRect(&ponto, &botaoVoltar)) {
                modoAdicionar = false;
                inputApelido.clear();
                inputNome.clear();
            }
        }
    } else {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            // Lógica para manipular eventos do SDL com jogadores (remover, selecionar)
        }
    }
}

std::string JogadaWidget::getApelido() const {
    return inputApelido;
}

std::string JogadaWidget::getNome() const {
    return inputNome;
}
