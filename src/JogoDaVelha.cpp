#include "JogoDaVelha.hpp"
#include <algorithm>

JogoDaVelha::JogoDaVelha() : JogoDeTabuleiro(3, 3) {}

bool JogoDaVelha::verificarVitoria(char jogador) const {
    // Verificar linhas
    for (int i = 0; i < linhas; ++i) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
            return true;
        }
    }
    // Verificar colunas
    for (int j = 0; j < colunas; ++j) {
        if (tabuleiro[0][j] == jogador && tabuleiro[1][j] == jogador && tabuleiro[2][j] == jogador) {
            return true;
        }
    }
    // Verificar diagonais
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
        return true;
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
        return true;
    }
    return false;
}

bool JogoDaVelha::tabuleiroCheio() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

bool JogoDaVelha::isBidimensional() const {
    return true;
}

void JogoDaVelha::jogadaIA(char jogador) {
    int melhorValor = -100;
    int melhorLinha = -1;
    int melhorColuna = -1;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (jogadaValida(i, j)) {
                tabuleiro[i][j] = jogador;
                int valorJogada = minimax(0, false, jogador);
                tabuleiro[i][j] = '-';
                if (valorJogada > melhorValor) {
                    melhorLinha = i;
                    melhorColuna = j;
                    melhorValor = valorJogada;
                }
            }
        }
    }

    if (melhorLinha != -1 && melhorColuna != -1) {
        tabuleiro[melhorLinha][melhorColuna] = jogador;
    }
}

int JogoDaVelha::minimax(int profundidade, bool isMaximizing, char jogador) {
    int pontuacao = avaliar();

    if (pontuacao == 10) return pontuacao - profundidade;
    if (pontuacao == -10) return pontuacao + profundidade;
    if (tabuleiroCheio()) return 0;

    if (isMaximizing) {
        int melhor = -100;
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (jogadaValida(i, j)) {
                    tabuleiro[i][j] = jogador;
                    melhor = std::max(melhor, minimax(profundidade + 1, false, jogador));
                    tabuleiro[i][j] = '-';
                }
            }
        }
        return melhor;
    } else {
        int melhor = 100;
        char adversario = (jogador == 'X') ? 'O' : 'X';
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (jogadaValida(i, j)) {
                    tabuleiro[i][j] = adversario;
                    melhor = std::min(melhor, minimax(profundidade + 1, true, jogador));
                    tabuleiro[i][j] = '-';
                }
            }
        }
        return melhor;
    }
}

int JogoDaVelha::avaliar() const {
    if (verificarVitoria('X')) return 10;
    if (verificarVitoria('O')) return -10;
    return 0;
}
