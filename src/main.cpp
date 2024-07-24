#include <iostream>
#include "Reversi.hpp"
#include "Lig4.hpp"

void jogar(JogoDeTabuleiro* jogo) {
    char jogador = 'X';
    while (!jogo->tabuleiroCheio()) {
        jogo->imprimirTabuleiro();

        int linha = -1, coluna = -1;
        if (jogo->isBidimensional()) {
            // Para jogos bidimensionais
            std::cout << "Turno do jogador " << jogador << " (linha coluna): ";
            std::cin >> linha >> coluna;
            linha -= 1; // Ajuste para o índice da linha
            coluna -= 1; // Ajuste para o índice da coluna
            if (jogo->jogadaValida(linha, coluna)) {
                jogo->fazerJogada(linha, coluna, jogador);
            } else {
                std::cout << "Jogada inválida. Tente novamente.\n";
                continue;
            }
        } else {
            // Para jogos unidimensionais
            std::cout << "Turno do jogador " << jogador << " (coluna): ";
            std::cin >> coluna;
            coluna -= 1; // Ajuste para o índice da coluna
            if (jogo->jogadaValida(coluna)) {
                jogo->fazerJogada(coluna, jogador);
            } else {
                std::cout << "Jogada inválida. Tente novamente.\n";
                continue;
            }
        }

        if (jogo->verificarVitoria(jogador)) {
            jogo->imprimirTabuleiro();
            std::cout << "Jogador " << jogador << " venceu!\n";
            return;
        }

        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    jogo->imprimirTabuleiro();
    std::cout << "Empate!\n";
}

int main() {
    int escolha;
    std::cout << "Escolha o jogo:\n1. Reversi\n2. Lig4\n";
    std::cin >> escolha;

    JogoDeTabuleiro* jogo = nullptr;

    if (escolha == 1) {
        jogo = new Reversi();
    } else if (escolha == 2) {
        jogo = new Lig4();
    } else {
        std::cout << "Escolha inválida.\n";
        return 1;
    }

    jogar(jogo);
    delete jogo;

    return 0;
}
