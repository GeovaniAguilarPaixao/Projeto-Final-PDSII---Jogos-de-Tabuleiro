#include "JogoDeTabuleiro.hpp"
#include <iostream>
#include <algorithm> // para std::fill
#include <iomanip> // para std::setw

JogoDeTabuleiro::JogoDeTabuleiro(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    tabuleiro = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        tabuleiro[i] = new char[colunas];
        std::fill(tabuleiro[i], tabuleiro[i] + colunas, '-');
    }
}

void JogoDeTabuleiro::imprimirTabuleiro() const {
    // Imprime a numeração das colunas
    std::cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        std::cout << std::setw(2) << j + 1;
    }
    std::cout << '\n';

    // Imprime o tabuleiro com a numeração das linhas
    for (int i = 0; i < linhas; ++i) {
        std::cout << std::setw(2) << i + 1 << ' '; // Numeração das linhas
        for (int j = 0; j < colunas; ++j) {
            std::cout << tabuleiro[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool JogoDeTabuleiro::jogadaValida(int linha, int coluna) const {
    // Implementação padrão para jogos com duas dimensões
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas && tabuleiro[linha][coluna] == '-';
}

bool JogoDeTabuleiro::fazerJogada(int linha, int coluna, char jogador) {
    // Implementação padrão para jogos com duas dimensões
    if (jogadaValida(linha, coluna)) {
        tabuleiro[linha][coluna] = jogador;
        return true;
    }
    return false;
}

bool JogoDeTabuleiro::jogadaValida(int coluna) const {
    // Implementação padrão para jogos com uma dimensão
    // Em jogos unidimensionais, você pode considerar a linha fixa ou verificar outras condições
    return coluna >= 0 && coluna < colunas && tabuleiro[0][coluna] == '-';
}

void JogoDeTabuleiro::fazerJogada(int coluna, char jogador) {
    // Implementação padrão para jogos com uma dimensão
    // Em jogos unidimensionais, você pode colocar a peça na primeira linha disponível ou semelhante
    for (int i = linhas - 1; i >= 0; --i) {
        if (tabuleiro[i][coluna] == '-') {
            tabuleiro[i][coluna] = jogador;
            break;
        }
    }
}
