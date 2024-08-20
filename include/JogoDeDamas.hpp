// #ifndef JOGO_DE_DAMAS_HPP
// #define JOGO_DE_DAMAS_HPP

// #include "JogoDeTabuleiro.hpp"
// #include <vector>

// class JogoDeDamas : public JogoDeTabuleiro {
// public:
//     JogoDeDamas();

//     void jogar();

// private:
//     bool fazerJogada(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, char jogador);
//     void inicializarTabuleiro();
//     int avaliarTabuleiro() const;
//     int minimax(int profundidade, bool maximizando, int alfa, int beta);
//     std::vector<std::vector<int>> obterJogadasValidas(char jogador);
//     void obterMelhorJogada(char jogador, int &linhaOrigem, int &colunaOrigem, int &linhaDestino, int &colunaDestino);
//     bool jogadaValida(int linhaDestino, int colunaDestino) const;
//     void desfazerJogada(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, char jogador, char pecaCapturada);
// };

// #endif 
