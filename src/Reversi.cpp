#include "Reversi.hpp"
#include <iostream>

Reversi::Reversi() : JogoDeTabuleiro(8, 8) {
    tabuleiro[3][3] = tabuleiro[4][4] = 'O';
    tabuleiro[3][4] = tabuleiro[4][3] = 'X';
}

bool Reversi::dentroDoTabuleiro(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Reversi::podeVirar(int linha, int coluna, int deltaLinha, int deltaColuna, char jogador) const {
    char oponente = (jogador == 'X') ? 'O' : 'X';
    linha += deltaLinha;
    coluna += deltaColuna;

    if (!dentroDoTabuleiro(linha, coluna) || tabuleiro[linha][coluna] != oponente) {
        return false;
    }

    linha += deltaLinha;
    coluna += deltaColuna;
    while (dentroDoTabuleiro(linha, coluna)) {
        if (tabuleiro[linha][coluna] == jogador) {
            return true;
        }
        if (tabuleiro[linha][coluna] == '-') {
            return false;
        }
        linha += deltaLinha;
        coluna += deltaColuna;
    }

    return false;
}

bool Reversi::jogadaValida(int linha, int coluna) const {
    if (tabuleiro[linha][coluna] != '-') {
        return false;
    }

    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if (deltaLinha != 0 || deltaColuna != 0) {
                if (podeVirar(linha, coluna, deltaLinha, deltaColuna, 'X') || 
                    podeVirar(linha, coluna, deltaLinha, deltaColuna, 'O')) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Reversi::fazerJogada(int linha, int coluna, char jogador) {
    if (!jogadaValida(linha, coluna)) {
        std::cout << "Jogada inválida!" << std::endl;
        return;
    }

    tabuleiro[linha][coluna] = jogador;

    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if (deltaLinha != 0 || deltaColuna != 0) {
                if (podeVirar(linha, coluna, deltaLinha, deltaColuna, jogador)) {
                    int l = linha + deltaLinha;
                    int c = coluna + deltaColuna;
                    while (tabuleiro[l][c] != jogador) {
                        tabuleiro[l][c] = jogador;
                        l += deltaLinha;
                        c += deltaColuna;
                    }
                }
            }
        }
    }
}

bool Reversi::verificarVitoria(char jogador) const {
    char oponente = (jogador == 'X') ? 'O' : 'X';
    int contJogador = 0, contOponente = 0;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] == jogador) {
                ++contJogador;
            } else if (tabuleiro[i][j] == oponente) {
                ++contOponente;
            }
        }
    }

    return contJogador > contOponente;
}

bool Reversi::tabuleiroCheio() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}
