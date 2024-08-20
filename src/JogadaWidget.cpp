#include "JogadaWidget.hpp"
#include <iostream>
#include <thread>
#include <chrono>

JogadaWidget::JogadaWidget(SDL_Renderer* renderer, TTF_Font* font, const std::string& dirData, MenuState& menuState)
    : renderer(renderer), font(font), dirData(dirData), menuState(menuState), modoAdicionar(false), cursor(0), inputApelidoAtivo(true), inputNomeAtivo(false) {
    jogada.carregarJogadores(dirData); 

    // Inicializando as caixas de texto
    caixaTextoApelido = { 200, 150, 200, 30 };
    caixaTextoNome = { 200, 200, 200, 30 };

    mutex = SDL_CreateMutex(); // Inicializando o mutex
}

JogadaWidget::~JogadaWidget() {
    jogada.salvarJogadores(dirData);
    SDL_DestroyMutex(mutex); // Liberando o mutex
}

void JogadaWidget::adicionarJogador(const std::string& apelido, const std::string& nome) {
    if (apelido.empty() || nome.empty()) {
        exibirAlerta(renderer, font, "Preencha todos os campos.");
        return;
    }
    jogada.adicionarJogador(apelido, nome);
    exibirAlerta(renderer, font, "Jogador adicionado com sucesso!");
}

void JogadaWidget::listarJogadores() {
    SDL_Color textColor = { 0, 0, 0, 255 };
    int y = 100;

    for (const auto& jogador : jogada.getJogadores()) {
        std::string apelido = jogador.first;
        std::string nome = jogador.second->getNome();
        renderText(renderer, font, apelido + " - " + nome, 100, y, textColor);
        y += 40;
    }
}

void JogadaWidget::tratarEvento(SDL_Event& e) {
    if (modoAdicionar) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            SDL_Point mousePoint = { e.button.x, e.button.y };

            SDL_Rect buttonVoltar = { 100, 400, 150, 50 };

            if (SDL_PointInRect(&mousePoint, &buttonVoltar)) {
                modoAdicionar = false;
                resetInput();
                menuState = JOGADORES_MENU; // Voltar para o menu de jogadores
                return;
            }
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_a) {
                modoAdicionar = true;
                std::thread(&JogadaWidget::inputNomeViaConsole, this).detach();
            }
        }
    } else {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            SDL_Point mousePoint = { e.button.x, e.button.y };
            int y = 100;

            for (const auto& jogador : jogada.getJogadores()) {
                SDL_Rect buttonSelect = { 420, y, 30, 30 };
                SDL_Rect buttonRemove = { 460, y, 30, 30 };

                if (SDL_PointInRect(&mousePoint, &buttonSelect)) {
                    // Ação de selecionar jogador
                    std::cout << "Selecionar jogador: " << jogador.first << std::endl;
                    jogadoresSelecionados.push_back(jogador.second);
                    if (jogadoresSelecionados.size() == 2) {
                        exibirAlerta(renderer, font, "Jogadores selecionados com sucesso.");
                        jogadoresSelecionados.clear();
                        menuState = JOGADORES_MENU;
                        return;
                    }
                } else if (SDL_PointInRect(&mousePoint, &buttonRemove)) {
                    // Ação de remover jogador
                    std::cout << "Remover jogador: " << jogador.first << std::endl;
                    jogada.removerJogador(jogador.first, dirData);
                    exibirAlerta(renderer, font, "Jogador removido com sucesso.");
                    menuState = JOGADORES_MENU;
                    break;
                }
                y += 80; 
            }
        }
    }
}

void JogadaWidget::inputNomeViaConsole() {
    renderAddJogador();

    // Primeiro, pede o nome
    std::string nome;
    std::cout << "Insira o nome: ";
    std::getline(std::cin, nome);

    SDL_LockMutex(mutex);
    inputNome = nome;
    inputNomeAtivo = true;  // Ativa a caixa de texto do Nome
    inputApelidoAtivo = false;
    SDL_UnlockMutex(mutex);

    renderAddJogador();

    // Agora, pede o apelido
    std::string apelido;
    std::cout << "Insira o apelido: ";
    std::getline(std::cin, apelido);

    SDL_LockMutex(mutex);
    inputApelido = apelido;
    inputNomeAtivo = false;
    inputApelidoAtivo = true;  // Ativa a caixa de texto do Apelido
    SDL_UnlockMutex(mutex);

    renderAddJogador();

    // Salva o jogador automaticamente após o apelido ser inserido
    SDL_LockMutex(mutex);
    adicionarJogador(inputApelido, inputNome);
    resetInput();
    modoAdicionar = false; // Sai do modo adicionar após salvar o jogador
    SDL_UnlockMutex(mutex);
    menuState = JOGADORES_MENU;
    return;
}

void JogadaWidget::handleBackspace() {
    if (inputApelidoAtivo && !inputApelido.empty()) {
        inputApelido.pop_back();
    } else if (inputNomeAtivo && !inputNome.empty()) {
        inputNome.pop_back();
    }
}

void JogadaWidget::handleTextInput(const char* text) {
    if (inputApelidoAtivo) {
        if (!isspace(text[0])) {
            inputApelido += text;
        }
    } else if (inputNomeAtivo) {
        if (!isspace(text[0])) {
            inputNome += text;
        }
    }
}

void JogadaWidget::resetInput() {
    inputApelido.clear();
    inputNome.clear();
    cursor = 0;
    inputApelidoAtivo = true;
    inputNomeAtivo = false;
}

void JogadaWidget::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    if (text.empty()) {
        std::cerr << "Erro: Tentativa de renderizar texto vazio." << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Erro ao criar a superfície de texto: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Erro ao criar a textura a partir da superfície: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void JogadaWidget::renderButton(SDL_Rect button, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &button);
    SDL_RenderDrawRect(renderer, &button); // Desenha o contorno do botão
}

void JogadaWidget::renderInputBox(SDL_Rect box, const std::string& text, SDL_Color color, bool isActive) {
    SDL_Color bgColor = isActive ? SDL_Color{ 255, 255, 255, 255 } : SDL_Color{ 200, 200, 200, 255 };
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &box);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawRect(renderer, &box);

    // Verifica se o texto não está vazio antes de renderizar
    if (!text.empty()) {
        renderText(renderer, font, text, box.x + 5, box.y + 5, color);
    }
}

void JogadaWidget::renderAddJogador() {
    SDL_Color textColor = { 0, 0, 0, 255 };

    renderText(renderer, font, "Adicionar Novo Jogador", 100, 50, textColor);

    renderText(renderer, font, "Nome:", 100, 200, textColor);
    renderInputBox(caixaTextoNome, inputNome, textColor, inputNomeAtivo);

    renderText(renderer, font, "Apelido:", 100, 150, textColor);
    renderInputBox(caixaTextoApelido, inputApelido, textColor, inputApelidoAtivo);

    SDL_RenderPresent(renderer);
}

void JogadaWidget::renderListarJogadores() {
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Rect buttonVoltar = { 100, 400, 150, 50 };
    bool continuarLoop = true;

    while (continuarLoop) {
        // Renderiza título
        renderText(renderer, font, "Lista de Jogadores", 50, 50, textColor);

        // Renderiza lista de jogadores com botões de selecionar/remover
        int y = 100;
        for (const auto& jogador : jogada.getJogadores()) {
            std::string apelido = jogador.first;
            std::string nome = jogador.second->getNome();

            // Renderiza nome do jogador
            renderText(renderer, font, apelido + " - " + nome, 50, y, textColor);

            // Renderiza estatísticas do jogador
            const auto& estatisticas = jogador.second->getEstatisticas();
            int yEstatisticas = y + 20; // posição inicial das estatísticas

            for (const auto& jogo : estatisticas) {
                renderText(renderer, font, jogo.first + " - V: " + std::to_string(jogo.second[0]) +
                    " D: " + std::to_string(jogo.second[1]) + " E: " + std::to_string(jogo.second[2]), 50, yEstatisticas, textColor);
                yEstatisticas += 20; // Ajusta a posição Y para cada linha de estatísticas
            }

            // Botão de selecionar jogador
            SDL_Rect buttonSelect = { 420, y, 30, 30 };
            renderButton(buttonSelect, { 0, 255, 0, 255 });
            renderText(renderer, font, "O", 425, y + 5, textColor);

            // Botão de remover jogador
            SDL_Rect buttonRemove = { 460, y, 30, 30 };
            renderButton(buttonRemove, { 255, 0, 0, 255 });
            renderText(renderer, font, "X", 465, y + 5, textColor);

            y += 80; 
        }

        // Renderiza botão voltar
        renderButton(buttonVoltar, { 255, 69, 0, 255 });
        renderText(renderer, font, "Voltar", 110, 410, textColor);

        SDL_RenderPresent(renderer);

        // Loop para tratar eventos
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            tratarEvento(e);

            // Verifica se o botão voltar foi clicado para sair do loop
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point mousePoint = { e.button.x, e.button.y };
                if (SDL_PointInRect(&mousePoint, &buttonVoltar)) {
                    // Atualiza o estado do menu para voltar ao menu anterior
                    menuState = JOGADORES_MENU; // Ou o estado correto para o menu anterior
                    continuarLoop = false;
                    break;
                }
            }

            // Verifica se o evento é para sair do programa
            if (e.type == SDL_QUIT) {
                continuarLoop = false;
                break;
            }
        }
    }
}

const std::vector<std::shared_ptr<Jogador>>& JogadaWidget::getJogadoresSelecionados() const {
    return jogadoresSelecionados;
}

void JogadaWidget::exibirAlerta(SDL_Renderer* renderer, TTF_Font* font, const std::string& mensagem) {
    SDL_Color cor = { 255, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, mensagem.c_str(), cor);
    if (!surface) {
        std::cerr << "Erro ao criar a superfície de alerta: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Erro ao criar a textura de alerta: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect = { 50, 350, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_RenderPresent(renderer);

    // Mantém a mensagem na tela por 3 segundos
    SDL_Delay(3000);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
