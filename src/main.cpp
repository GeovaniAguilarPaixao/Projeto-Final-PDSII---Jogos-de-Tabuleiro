#include <iostream>
#include <fstream>
#include <map>
#include "Reversi.hpp"
#include "Lig4.hpp"
#include "JogoDaVelha.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"

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
                bool verificaJogada = jogo->fazerJogada(linha, coluna, jogador);
                if(!verificaJogada){
                    jogador = (jogador == 'X') ? 'O' : 'X';
                }
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
    // TESTES DA CLASSE JOGADA
    // MANTER COMO COMENTÁRIO
     std::string data_path;
     data_path = "data";
     std::unique_ptr<Jogada> jogada = std::make_unique<Jogada>();
     jogada->carregarJogadores(data_path);
     jogada->listarJogadores();
     jogada->adicionarJogador("Jogador1","Jogador 1");
     jogada->adicionarJogador("Jogador2","Jogador 2");
     jogada->adicionarJogador("Jogador3", "Jogador 3");
     jogada->listarJogadores();
     jogada->removerJogador("Jogador3", "Jogador 3");
     jogada->listarJogadores();
     jogada->adicionarJogador("Jogador4", "Jogador 4");
     jogada->listarJogadores();
     jogada->salvarJogadores(data_path);
     jogada->removerJogador("Jogador4",data_path);
     jogada->listarJogadores();

    
    
    return 0;
}
