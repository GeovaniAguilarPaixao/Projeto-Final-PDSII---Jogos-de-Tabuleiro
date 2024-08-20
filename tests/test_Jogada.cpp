#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

// Função auxiliar para criar um arquivo de jogador de teste
void criarArquivoJogador(const std::string& apelido, const std::string& nome, const std::string& dir) {
    std::string caminho = dir + "/" + apelido + ".txt";
    std::ofstream arquivo(caminho);
    arquivo << apelido << '\n' << nome << '\n';
    arquivo << "Jogo1 1 2 3\n";  // Exemplo de estatísticas
    arquivo << "---\n";
    arquivo.close();
}

TEST_SUITE("Teste da classe Jogada") {
    TEST_CASE("Teste adicionarJogador() e listarJogadores()") {
        Jogada jogada;

        jogada.adicionarJogador("apelido1", "Nome Jogador 1");
        jogada.adicionarJogador("apelido2", "Nome Jogador 2");

        // redirecionar o output do terminal para a string oss
        std::ostringstream oss;
        // salvar o buffer original
        std::streambuf* coutbuf = std::cout.rdbuf();
        // redirecionar o output para a string oss
        std::cout.rdbuf(oss.rdbuf());

        jogada.listarJogadores();

        // restaurando o buffer
        std::cout.rdbuf(coutbuf);

        std::string output = oss.str();
        CHECK(output.find("apelido1 Nome Jogador 1") != std::string::npos);
        CHECK(output.find("apelido2 Nome Jogador 2") != std::string::npos);
    }

    TEST_CASE("Teste removerJogador()") {
        Jogada jogada;
        jogada.adicionarJogador("apelido1", "Nome Jogador 1");

        jogada.removerJogador("apelido1", "./data");

        CHECK(jogada.selecionarJogador("apelido1") == nullptr);
    }

    TEST_CASE("Carregar e salvar jogadores") {
        // Criar diretório de teste
        std::string dir_data = "./data";
        std::filesystem::create_directory(dir_data);

        // Criar arquivos de jogador de teste
        criarArquivoJogador("apelido1", "Nome Jogador 1", dir_data);
        criarArquivoJogador("apelido2", "Nome Jogador 2", dir_data);

        Jogada jogada;
        jogada.carregarJogadores(dir_data);

        CHECK(jogada.selecionarJogador("apelido1") != nullptr);
        CHECK(jogada.selecionarJogador("apelido2") != nullptr);

        // Excluir os jogadores criados para o teste
        jogada.removerJogador("apelido1", "./data");
        jogada.removerJogador("apelido2", "./data");
    }
}