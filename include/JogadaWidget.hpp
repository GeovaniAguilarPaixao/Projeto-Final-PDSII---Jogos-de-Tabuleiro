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
    
    void desenhar();
    void adicionarJogador(const std::string& apelido, const std::string& nome);
    void removerJogador(const std::string& apelido);
    void listarJogadores();

    void carregarJogadores();
    void salvarJogadores();
    void tratarEvento(SDL_Event& e);

    
private:
    void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
    void exibirAlerta(SDL_Renderer* renderer, TTF_Font* font, const std::string& mensagem);

    std::string inputApelido;
    std::string inputNome;
    SDL_Rect caixaTexto;


    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string dirData;
    bool modoAdicionar;
    int cursor;
    Jogada jogada;
};

#endif // JOGADA_WIDGET_HPP
