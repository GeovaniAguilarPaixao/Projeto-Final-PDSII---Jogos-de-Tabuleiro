#include "JogadaWidget.hpp"

JogadaWidget::JogadaWidget(SDL_Renderer* renderer, TTF_Font* font, const std::string& dirData)
    : renderer(renderer), font(font), dirData(dirData), modoAdicionar(false), cursor(0) {
    jogada.carregarJogadores(dirData);
}



JogadaWidget::~JogadaWidget() {
    salvarJogadores();
}

void JogadaWidget::carregarJogadores() {
    std::ifstream file(dirData + "/jogadores.txt");
    if (file.is_open()) {
        std::string apelido, nome;
        while (file >> apelido >> nome) {
            jogada.adicionarJogador(apelido, nome);
        }
        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo de jogadores." << std::endl;
    }
}

void JogadaWidget::salvarJogadores() {
    std::ofstream file(dirData + "/jogadores.txt");
    if (file.is_open()) {
        for (const auto& jogador : jogada.getJogadores()) {
            file << jogador.first << " " << jogador.second->getNome() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Erro ao salvar o arquivo de jogadores." << std::endl;
    }
}

void JogadaWidget::adicionarJogador(const std::string& apelido, const std::string& nome) {
    jogada.adicionarJogador(apelido, nome);
}

void JogadaWidget::removerJogador(const std::string& apelido) {
    jogada.removerJogador(apelido, dirData);
}

void JogadaWidget::listarJogadores() {
    SDL_RenderClear(renderer);
    int y = 50;
    for (const auto& jogador : jogada.getJogadores()) {
        renderText(renderer, font, jogador.first + " - " + jogador.second->getNome(), 50, y);
        y += 40;
    }

    if (jogada.getJogadores().size() < 2) {
        exibirAlerta(renderer, font, "Selecione pelo menos dois jogadores.");
    }

    SDL_RenderPresent(renderer);
}

void JogadaWidget::tratarEvento(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (modoAdicionar) {
            if (!inputApelido.empty() && !inputNome.empty()) {
                adicionarJogador(inputApelido, inputNome);
                inputApelido.clear();
                inputNome.clear();
                modoAdicionar = false;
            } else {
                exibirAlerta(renderer, font, "Preencha todos os campos.");
            }
        }
    } else if (e.type == SDL_KEYDOWN) {
        if (modoAdicionar) {
            if (e.key.keysym.sym == SDLK_BACKSPACE) {
                if (cursor > 0) {
                    if (!inputNome.empty()) {
                        inputNome.pop_back();
                    } else if (!inputApelido.empty()) {
                        inputApelido.pop_back();
                    }
                    cursor--;
                }
            } else if (e.key.keysym.sym == SDLK_RETURN) {
                if (!inputApelido.empty() && !inputNome.empty()) {
                    adicionarJogador(inputApelido, inputNome);
                    inputApelido.clear();
                    inputNome.clear();
                    modoAdicionar = false;
                    cursor = 0;
                } else {
                    exibirAlerta(renderer, font, "Preencha todos os campos.");
                }
            }
        } else {
            if (e.key.keysym.sym == SDLK_a) {
                modoAdicionar = true;
            }
        }
    } else if (e.type == SDL_TEXTINPUT) {
        if (modoAdicionar) {
            if (inputApelido.empty() || !inputNome.empty()) {
                inputApelido += e.text.text;
            } else {
                inputNome += e.text.text;
            }
            cursor++;
        }
    }
}

void JogadaWidget::desenhar() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    int y = 50;
    for (const auto& jogador : jogada.getJogadores()) {
        renderText(renderer, font, jogador.first + " - " + jogador.second->getNome(), 50, y);
        y += 40;
    }

    if (modoAdicionar) {
        renderText(renderer, font, "Adicionar Jogador: " + inputApelido + " " + inputNome, caixaTexto.x, caixaTexto.y);
    }

    SDL_RenderPresent(renderer);
}

void JogadaWidget::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color cor = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), cor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void JogadaWidget::exibirAlerta(SDL_Renderer* renderer, TTF_Font* font, const std::string& mensagem) {
    SDL_Color cor = { 255, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, mensagem.c_str(), cor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { 50, 350, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}
