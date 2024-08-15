#include "JogoDaVelha.hpp"
#include <iostream>

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
void JogoDaVelha::jogadaIA(char jogador) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (jogadaValida(i, j)) {
                tabuleiro[i][j] = jogador;
                if (verificarVitoria(jogador)) {
                    return;
                }
                tabuleiro[i][j] = '-';
            }
        }
    }

    char adversario = (jogador == 'X') ? 'O' : 'X';
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (jogadaValida(i, j)) {
                tabuleiro[i][j] = adversario;
                if (verificarVitoria(adversario)) {
                    tabuleiro[i][j] = jogador;
                    return;
                }
                tabuleiro[i][j] = '-';
            }
        }
    }

    while (true) {
        int i = rand() % linhas;
        int j = rand() % colunas;
        if (jogadaValida(i, j)) {
            tabuleiro[i][j] = jogador;
            break;
        }
    }
}