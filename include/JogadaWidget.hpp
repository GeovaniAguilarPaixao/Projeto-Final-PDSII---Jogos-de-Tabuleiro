#ifndef JOGADA_WIDGET_HPP
#define JOGADA_WIDGET_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Jogada.hpp"

class JogadaWidget {
public:
    JogadaWidget(SDL_Renderer* renderer, TTF_Font* font, const std::string& dirData);
    ~JogadaWidget();

    void carregarJogadores();
    void salvarJogadores();
    void adicionarJogador(const std::string& apelido, const std::string& nome);
    void removerJogador(const std::string& apelido);
    void listarJogadores();
    void desenhar();
    void tratarEvento(SDL_Event& e);

    std::string getApelido() const;
    std::string getNome() const;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string dirData;
    Jogada jogada;

    SDL_Rect caixaTexto;
    std::string inputApelido;
    std::string inputNome;
    int cursor;
    bool modoAdicionar;

    void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
};

#endif
