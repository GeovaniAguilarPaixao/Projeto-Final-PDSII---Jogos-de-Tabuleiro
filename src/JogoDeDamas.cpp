// precisa adicionar seguintes funções na classe JogoDeTabuleiro:
// int JogoDeTabuleiro::getLinhas() const { return linhas; }
// int JogoDeTabuleiro::getColunas() const { return colunas; }

// #include "JogoDeDamas.hpp"
// #include <iostream>
// #include <algorithm>
// #include <cmath>

// JogoDeDamas::JogoDeDamas() : JogoDeTabuleiro(8, 8) {
//     inicializarTabuleiro();
// }

// void JogoDeDamas::jogar() {
//     char jogadorAtual = 'X';
//     while (true) {
//         imprimirTabuleiro();

//         if (jogadorAtual == 'X') {
//             std::cout << "Jogador Preto, faça um movimento (de: linha coluna para: linha coluna): ";
//             int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;
//             std::cin >> linhaOrigem >> colunaOrigem >> linhaDestino >> colunaDestino;
//             linhaOrigem--;
//             colunaOrigem--;
//             linhaDestino--;
//             colunaDestino--;
//             if (fazerJogada(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, jogadorAtual)) {
//                 if (linhaDestino == getLinhas() - 1) {
//                     std::cout << "Preto vence por chegar ao final do tabuleiro!" << std::endl;
//                     break;
//                 }
//                 jogadorAtual = 'O';
//             } else {
//                 std::cout << "Movimento inválido. Tente novamente." << std::endl;
//             }
//         } else {
//             std::cout << "IA está fazendo um movimento..." << std::endl;
//             int melhorLinhaOrigem, melhorColunaOrigem, melhorLinhaDestino, melhorColunaDestino;
//             obterMelhorJogada(jogadorAtual, melhorLinhaOrigem, melhorColunaOrigem, melhorLinhaDestino, melhorColunaDestino);

//             if (melhorLinhaOrigem != -1) {
//                 fazerJogada(melhorLinhaOrigem, melhorColunaOrigem, melhorLinhaDestino, melhorColunaDestino, jogadorAtual);
//                 if (melhorLinhaDestino == 0) {
//                     std::cout << "Branco vence por chegar ao final do tabuleiro!" << std::endl;
//                     break;
//                 }
//                 jogadorAtual = 'X';
//             } else {
//                 std::cout << "A IA não tem movimentos válidos e perdeu." << std::endl;
//                 break;
//             }
//         }
//     }
// }

// bool JogoDeDamas::fazerJogada(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, char jogador) {
//     if (linhaOrigem < 0 || linhaOrigem >= getLinhas() || colunaOrigem < 0 || colunaOrigem >= getColunas() ||
//         linhaDestino < 0 || linhaDestino >= getLinhas() || colunaDestino < 0 || colunaDestino >= getColunas()) {
//         return false;
//     }

//     char peca = tabuleiro[linhaOrigem][colunaOrigem];
//     if (peca != jogador) {
//         return false;
//     }

//     if (tabuleiro[linhaDestino][colunaDestino] != '-') {
//         return false;
//     }

//     int deltaLinha = linhaDestino - linhaOrigem;
//     int deltaColuna = colunaDestino - colunaOrigem;

//     // Movimento simples
//     if (std::abs(deltaLinha) == 1 && std::abs(deltaColuna) == 1) {
//         if ((jogador == 'X' && deltaLinha > 0) || (jogador == 'O' && deltaLinha < 0)) {
//             tabuleiro[linhaDestino][colunaDestino] = peca;
//             tabuleiro[linhaOrigem][colunaOrigem] = '-';
//             return true;
//         }
//     }
//     // Movimento de captura
//     else if (std::abs(deltaLinha) == 2 && std::abs(deltaColuna) == 2) {
//         int linhaMeio = (linhaOrigem + linhaDestino) / 2;
//         int colunaMeio = (colunaOrigem + colunaDestino) / 2;
//         char pecaCapturada = tabuleiro[linhaMeio][colunaMeio];
//         if (pecaCapturada != '-' && pecaCapturada != jogador) {
//             tabuleiro[linhaDestino][colunaDestino] = peca;
//             tabuleiro[linhaOrigem][colunaOrigem] = '-';
//             tabuleiro[linhaMeio][colunaMeio] = '-';
//             return true;
//         }
//     }

//     return false;
// }

// void JogoDeDamas::inicializarTabuleiro() {
//     for (int i = 0; i < 3; ++i) {
//         for (int j = (i % 2); j < getColunas(); j += 2) {
//             tabuleiro[i][j] = 'X';
//         }
//     }
//     for (int i = 5; i < getLinhas(); ++i) {
//         for (int j = (i % 2); j < getColunas(); j += 2) {
//             tabuleiro[i][j] = 'O';
//         }
//     }
// }

// int JogoDeDamas::avaliarTabuleiro() const {
//     int pontuacao = 0;
//     for (int i = 0; i < getLinhas(); ++i) {
//         for (int j = 0; j < getColunas(); ++j) {
//             if (tabuleiro[i][j] == 'X') {
//                 pontuacao += 1;
//             } else if (tabuleiro[i][j] == 'O') {
//                 pontuacao -= 1;
//             }
//         }
//     }
//     return pontuacao;
// }

// int JogoDeDamas::minimax(int profundidade, bool maximizando, int alfa, int beta) {
//     if (profundidade == 0) {
//         return avaliarTabuleiro();
//     }

//     char jogadorAtual = maximizando ? 'X' : 'O';
//     std::vector<std::vector<int>> jogadasValidas = obterJogadasValidas(jogadorAtual);

//     if (jogadasValidas.empty()) {
//         return maximizando ? -100 : 100;
//     }

//     if (maximizando) {
//         int melhorPontuacao = -100;
//         for (const auto& jogada : jogadasValidas) {
//             char pecaCapturada = '-';
//             if (std::abs(jogada[2] - jogada[0]) == 2) {
//                 int linhaMeio = (jogada[0] + jogada[2]) / 2;
//                 int colunaMeio = (jogada[1] + jogada[3]) / 2;
//                 pecaCapturada = tabuleiro[linhaMeio][colunaMeio];
//             }
//             fazerJogada(jogada[0], jogada[1], jogada[2], jogada[3], jogadorAtual);
//             int pontuacao = minimax(profundidade - 1, false, alfa, beta);
//             desfazerJogada(jogada[0], jogada[1], jogada[2], jogada[3], jogadorAtual, pecaCapturada);
//             melhorPontuacao = std::max(melhorPontuacao, pontuacao);
//             alfa = std::max(alfa, melhorPontuacao);
//             if (beta <= alfa) {
//                 break;
//             }
//         }
//         return melhorPontuacao;
//     } else {
//         int melhorPontuacao = 100;
//         for (const auto& jogada : jogadasValidas) {
//             char pecaCapturada = '-';
//             if (std::abs(jogada[2] - jogada[0]) == 2) {
//                 int linhaMeio = (jogada[0] + jogada[2]) / 2;
//                 int colunaMeio = (jogada[1] + jogada[3]) / 2;
//                 pecaCapturada = tabuleiro[linhaMeio][colunaMeio];
//             }
//             fazerJogada(jogada[0], jogada[1], jogada[2], jogada[3], jogadorAtual);
//             int pontuacao = minimax(profundidade - 1, true, alfa, beta);
//             desfazerJogada(jogada[0], jogada[1], jogada[2], jogada[3], jogadorAtual, pecaCapturada);
//             melhorPontuacao = std::min(melhorPontuacao, pontuacao);
//             beta = std::min(beta, melhorPontuacao);
//             if (beta <= alfa) {
//                 break;
//             }
//         }
//         return melhorPontuacao;
//     }
// }

// std::vector<std::vector<int>> JogoDeDamas::obterJogadasValidas(char jogador) {
//     std::vector<std::vector<int>> jogadasValidas;
//     int direcoes[2][2] = {{1, -1}, {1, 1}}; // Movimentos para peças 'X'
//     if (jogador == 'O') {
//         direcoes[0][0] = -1;
//         direcoes[1][0] = -1; // Movimentos para peças 'O'
//     }

//     for (int i = 0; i < getLinhas(); ++i) {
//         for (int j = 0; j < getColunas(); ++j) {
//             if (tabuleiro[i][j] == jogador) {
//                 for (const auto& direcao : direcoes) {
//                     int di = direcao[0];
//                     int dj = direcao[1];
//                     int linhaDestino = i + di;
//                     int colunaDestino = j + dj;

//                     if (jogadaValida(linhaDestino, colunaDestino)) {
//                         // Movimento simples
//                         if (std::abs(di) == 1 && std::abs(dj) == 1) {
//                             jogadasValidas.push_back({i, j, linhaDestino, colunaDestino});
//                         }
//                         // Movimento de captura
//                         else if (std::abs(di) == 2 && std::abs(dj) == 2) {
//                             int linhaMeio = i + di / 2;
//                             int colunaMeio = j + dj / 2;
//                             if (tabuleiro[linhaMeio][colunaMeio] != '-' && tabuleiro[linhaMeio][colunaMeio] != jogador) {
//                                 jogadasValidas.push_back({i, j, linhaDestino, colunaDestino});
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return jogadasValidas;
// }

// void JogoDeDamas::obterMelhorJogada(char jogador, int &linhaOrigem, int &colunaOrigem, int &linhaDestino, int &colunaDestino) {
//     int melhorPontuacao = -100;
//     std::vector<std::vector<int>> jogadasValidas = obterJogadasValidas(jogador);

//     for (const auto& jogada : jogadasValidas) {
//         char pecaCapturada = '-';
//         if (std::abs(jogada[2] - jogada[0]) == 2) {
//             int linhaMeio = (jogada[0] + jogada[2]) / 2;
//             int colunaMeio = (jogada[1] + jogada[3]) / 2;
//             pecaCapturada = tabuleiro[linhaMeio][colunaMeio];
//         }
//         fazerJogada(jogada[0], jogada[1], jogada[2], jogada[3], jogador);
//         int pontuacao = minimax(3, false, -100, 100);
//         desfazerJogada(jogada[0], jogada[1], jogada[2], jogada[3], jogador, pecaCapturada);

//         if (pontuacao > melhorPontuacao) {
//             melhorPontuacao = pontuacao;
//             linhaOrigem = jogada[0];
//             colunaOrigem = jogada[1];
//             linhaDestino = jogada[2];
//             colunaDestino = jogada[3];
//         }
//     }
// }

// bool JogoDeDamas::jogadaValida(int linhaDestino, int colunaDestino) const {
//     return linhaDestino >= 0 && linhaDestino < getLinhas() &&
//            colunaDestino >= 0 && colunaDestino < getColunas() &&
//            tabuleiro[linhaDestino][colunaDestino] == '-';
// }

// void JogoDeDamas::desfazerJogada(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, char jogador, char pecaCapturada) {
//     tabuleiro[linhaOrigem][colunaOrigem] = jogador;
//     tabuleiro[linhaDestino][colunaDestino] = '-';
//     if (pecaCapturada != '-') {
//         int linhaMeio = (linhaOrigem + linhaDestino) / 2;
//         int colunaMeio = (colunaOrigem + colunaDestino) / 2;
//         tabuleiro[linhaMeio][colunaMeio] = pecaCapturada;
//     }
// }
