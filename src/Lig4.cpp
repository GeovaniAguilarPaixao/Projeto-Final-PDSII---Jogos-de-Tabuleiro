#include "Lig4.hpp"
#include <iostream>

Lig4::Lig4() : JogoDeTabuleiro(6, 7) {}

bool Lig4::dentroDoTabuleiro(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Lig4::jogadaValida(int coluna) const {
    return dentroDoTabuleiro(0, coluna) && tabuleiro[0][coluna] == '-';
}

void Lig4::fazerJogada(int coluna, char jogador) {
    if (!jogadaValida(coluna)) {
        std::cout << "Jogada inválida!" << std::endl;
        return;
    }

    for (int linha = linhas - 1; linha >= 0; --linha) {
        if (tabuleiro[linha][coluna] == '-') {
            tabuleiro[linha][coluna] = jogador;
            break;
        }
    }
}

bool Lig4::verificarDirecao(int linha, int coluna, int deltaLinha, int deltaColuna, char jogador) const {
    int cont = 0;
    for (int i = 0; i < 4; ++i) {
        int l = linha + i * deltaLinha;
        int c = coluna + i * deltaColuna;
        if (dentroDoTabuleiro(l, c) && tabuleiro[l][c] == jogador) {
            ++cont;
        } else {
            break;
        }
    }
    return cont == 4;
}

bool Lig4::verificarVitoria(char jogador) const {
    for (int linha = 0; linha < linhas; ++linha) {
        for (int coluna = 0; coluna < colunas; ++coluna) {
            if (tabuleiro[linha][coluna] == jogador) {
                if (verificarDirecao(linha, coluna, 1, 0, jogador) ||
                    verificarDirecao(linha, coluna, 0, 1, jogador) ||
                    verificarDirecao(linha, coluna, 1, 1, jogador) ||
                    verificarDirecao(linha, coluna, 1, -1, jogador)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Lig4::tabuleiroCheio() const {
    for (int coluna = 0; coluna < colunas; ++coluna) {
        if (tabuleiro[0][coluna] == '-') {
            return false;
        }
    }
    return true;
}
