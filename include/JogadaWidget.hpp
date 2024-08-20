#ifndef JOGADA_WIDGET_HPP
#define JOGADA_WIDGET_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "MenuState.hpp"
#include "Jogada.hpp" 

class JogadaWidget {
public:
    JogadaWidget(SDL_Renderer* renderer, TTF_Font* font, const std::string& dirData, MenuState& menuState);
    ~JogadaWidget();

    void renderListarJogadores();
    void inputNomeViaConsole();
    const std::vector<std::shared_ptr<Jogador>>& getJogadoresSelecionados() const; // Método para retornar jogadores selecionados

private:
    void handleBackspace();
    void handleTextInput(const char* text);
    void resetInput();
    void listarJogadores();
    void renderAddJogador();
    void tratarEvento(SDL_Event& e);
    void adicionarJogador(const std::string& apelido, const std::string& nome);
    void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);
    void renderButton(SDL_Rect button, SDL_Color color);
    void renderInputBox(SDL_Rect box, const std::string& text, SDL_Color color, bool isActive);
    void exibirAlerta(SDL_Renderer* renderer, TTF_Font* font, const std::string& mensagem);

    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string dirData;
    MenuState& menuState; // Referência para o estado do menu
    std::vector<std::shared_ptr<Jogador>> jogadoresSelecionados;

    Jogada jogada; // Adicione a variável jogada

    SDL_Rect caixaTextoApelido;
    SDL_Rect caixaTextoNome;
    bool modoAdicionar;
    int cursor;
    bool inputApelidoAtivo;
    bool inputNomeAtivo;
    std::string inputApelido;
    std::string inputNome;
    SDL_mutex* mutex;
};

#endif // JOGADA_WIDGET_HPP
