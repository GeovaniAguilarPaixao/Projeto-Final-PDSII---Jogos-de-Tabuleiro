#include "Reversi.hpp"
#include <iostream>
#include <vector>

Reversi::Reversi() : JogoDeTabuleiro(8, 8) {
    tabuleiro[3][3] = 'O';
    tabuleiro[3][4] = 'X';
    tabuleiro[4][3] = 'X';
    tabuleiro[4][4] = 'O';
}

bool Reversi::dentroDoTabuleiro(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Reversi::jogadaValida(int linha, int coluna, char jogador) const {
    if (!dentroDoTabuleiro(linha, coluna) || tabuleiro[linha][coluna] != '-') {
        return false;
    }

    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if (deltaLinha != 0 || deltaColuna != 0) {
                if (podeVirar(linha, coluna, deltaLinha, deltaColuna, jogador)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Reversi::podeVirar(int linha, int coluna, int deltaLinha, int deltaColuna, char jogador) const {
    int i = linha + deltaLinha;
    int j = coluna + deltaColuna;
    bool encontrouOponente = false;

    while (dentroDoTabuleiro(i, j) && tabuleiro[i][j] != '-' && tabuleiro[i][j] != jogador) {
        encontrouOponente = true;
        i += deltaLinha;
        j += deltaColuna;
    }

    return encontrouOponente && dentroDoTabuleiro(i, j) && tabuleiro[i][j] == jogador;
}

void Reversi::fazerJogada(int linha, int coluna, char jogador) {
    if (!jogadaValida(linha, coluna, jogador)) {
        std::cout << "Jogada inválida\n";
        return;
    }

    tabuleiro[linha][coluna] = jogador;

    const std::vector<std::pair<int, int>> direcoes = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},         {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto& [deltaLinha, deltaColuna] : direcoes) {
        if (podeVirar(linha, coluna, deltaLinha, deltaColuna, jogador)) {
            int r = linha + deltaLinha;
            int c = coluna + deltaColuna;
            char adversario = (jogador == 'X') ? 'O' : 'X';

            while (tabuleiro[r][c] == adversario) {
                tabuleiro[r][c] = jogador;
                r += deltaLinha;
                c += deltaColuna;
            }
        }
    }
}

bool Reversi::verificarVitoria(char jogador) const {
    if (tabuleiroCheio() || (!possuiJogadaValida('X') && !possuiJogadaValida('O'))) {
        int contJogador = 0;
        int contAdversario = 0;
        char adversario = (jogador == 'X') ? 'O' : 'X';

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (tabuleiro[i][j] == jogador) {
                    ++contJogador;
                } else if (tabuleiro[i][j] == adversario) {
                    ++contAdversario;
                }
            }
        }

        return contJogador > contAdversario;
    }

    return false;
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

bool Reversi::possuiJogadaValida(char jogador) const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (jogadaValida(i, j, jogador)) {
                return true;
            }
        }
    }
    return false;
}
