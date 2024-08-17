#include "Jogada.hpp"

void Jogada::carregarJogadores(std::string dir_data){
    // confere se o caminho existe e é um diretório
    if (!std::filesystem::exists(dir_data) || !std::filesystem::is_directory(dir_data)) {
        std::cout << "Não foi possível carregar o histórico de jogadores!" << std::endl;
    }
    else {
        // itera sobre todos o conteúdo no diretório
        for (const auto& file : std::filesystem::directory_iterator(dir_data)) {
            // confere se o conteúdo é um arquivo e se a extensão é .txt
            if (file.is_regular_file() && file.path().extension() == ".txt") {
                std::string filePath = file.path().string();
                std::ifstream f_jogador(filePath);
                if (!f_jogador.is_open()) {
                    continue;
                }
                std::unique_ptr<Jogador> jogador = std::make_unique<Jogador>();
                jogador->carregar(f_jogador);
                f_jogador.close();
                this->jogadores[jogador->getApelido()] = std::move(jogador);
            }
        }
    }
}

const std::map<std::string, std::unique_ptr<Jogador>>& Jogada::getJogadores() const {
    return jogadores;
}

void Jogada::salvarJogadores(std::string dir_data) const{
    // confere se o caminho existe e é um diretório
    if (!std::filesystem::exists(dir_data) || !std::filesystem::is_directory(dir_data)) {
        std::cout << "Não foi possível salvar o histórico de jogadores!" << std::endl;
    }
    else {
        for (const auto& it : this->jogadores) {
            std::string nome_arquivo = dir_data + "/" + it.second->getApelido() + ".txt";
            std::ofstream f_jogador(nome_arquivo);
            if (!f_jogador.is_open()) {
                continue;
            }
            else {
                it.second->salvar(f_jogador);
                f_jogador.close();
            }
        }
    }
}

void Jogada::adicionarJogador(std::string apelido, std::string nome) {
    auto it =  this->jogadores.find(apelido);
    // caso o jogador já exista
    if (it != this->jogadores.end()) {
        std::cout << "ERRO: jogador repetido" << std::endl;
    }
    // caso jogador não exista
    else {
        std::unique_ptr<Jogador> jogador = std::make_unique<Jogador>(apelido, nome);
        this->jogadores[jogador->getApelido()] = std::move(jogador);
        std::cout << "Jogador " << apelido << " cadastrado com sucesso" << std::endl;
    }
}

void Jogada::removerJogador(std::string apelido, std::string dir_data) {
    auto it =  this->jogadores.find(apelido);
    // caso o jogador exista
    if (it != this->jogadores.end()) {
        std::string apelido = it->second->getApelido();
        std::string f_jogador = dir_data + "/" + apelido + ".txt";
        // exclusao do arquivo
        if (std::filesystem::remove(f_jogador)) {
            // caso arquivo seja excluido: retorna true
            // caso arquivo não exista: retorna false (pode acontecer se jogador for criado e excluido em uma mesma execucao)
        }
        this->jogadores.erase(it);
        std::cout << "Jogador " << apelido << " removido com sucesso" << std::endl;

    }
    // caso jogador não exista
    else {
        std::cout << "ERRO: jogador inexistente" << std::endl;
    }
}

void Jogada::listarJogadores() const {
    for (const auto& it : this->jogadores) {
        it.second->listarEstatisticas();
    }
}

Jogador* Jogada::selecionarJogador(std::string apelido) const {
    auto it =  this->jogadores.find(apelido);
    // caso o jogador exista
    if (it != this->jogadores.end()) {
        return it->second.get();
    }
    // caso jogador não exista
    else {
        return nullptr;
    }
}