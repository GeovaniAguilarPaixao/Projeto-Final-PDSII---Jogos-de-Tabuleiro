#include "Jogada.hpp"

// Carrega os dados de jogadores armazenados no diretório dir_data
void Jogada::carregarJogadores(std::string dir_data){
    // Confere se o caminho existe e é um diretório
    if (!std::filesystem::exists(dir_data) || !std::filesystem::is_directory(dir_data)) {
        std::cout << "Não foi possível carregar o histórico de jogadores!" << std::endl;
    }
    else {
        // Itera sobre todos o conteúdo no diretório
        for (const auto& file : std::filesystem::directory_iterator(dir_data)) {
            // Confere se o conteúdo é um arquivo e se a extensão é .txt
            if (file.is_regular_file() && file.path().extension() == ".txt") {
                // Converte o caminho para string (necessário para o fluxo ifstream)
                std::string filePath = file.path().string();
                // Abre o arquivo
                std::ifstream f_jogador(filePath);
                // Verifica se o arquivo foi aberto com sucesso
                if (!f_jogador.is_open()) {
                    continue;
                }
                // Instancia um ponteiro inteligente para jogador 
                std::shared_ptr<Jogador> jogador (new Jogador());
                // Carrega as informações do jogador
                jogador->carregar(f_jogador);
                // Fecha o arquivo
                f_jogador.close();
                // Move o ponteiro inteligente para o map de jogadores
                this->jogadores[jogador->getApelido()] = std::move(jogador);
            }
        }
    }
}

// Retorna o map de jogadores
const std::map<std::string, std::shared_ptr<Jogador>>& Jogada::getJogadores() const {
    return this->jogadores;
}

// Salva os dados dos jogadores no diretório dir_data
void Jogada::salvarJogadores(std::string dir_data) const{
    // Confere se o caminho existe e é um diretório
    if (!std::filesystem::exists(dir_data) || !std::filesystem::is_directory(dir_data)) {
        std::cout << "Não foi possível salvar o histórico de jogadores!" << std::endl;
    }
    // Caso o caminho exista e seja um diretório
    else {
        // Iterador para percorrer o map de jogadores
        for (const auto& it : this->jogadores) {
            // Define o caminho e o nome do arquivo
            std::string nome_arquivo = dir_data + "/" + it.second->getApelido() + ".txt";
            // Abre o arquivo para escrita
            std::ofstream f_jogador(nome_arquivo);
            // Verifica se o arquivo foi aberto com sucesso
            if (!f_jogador.is_open()) {
                continue;
            }
            // Caso o arquivo tenha sido aberto com sucesso
            else {
                // Passa o fluxo de saída como parâmetro para o método salvar() do objeto jogador 
                it.second->salvar(f_jogador);
                // Fecha o arquivo
                f_jogador.close();
            }
        }
    }
}
// Adiciona um jogador à jogada
void Jogada::adicionarJogador(std::string apelido, std::string nome) {
    // Verifica se já existe jogador com o mesmo apelido
    auto it =  this->jogadores.find(apelido);
    // Caso o jogador já exista
    if (it != this->jogadores.end()) {
        std::cout << "ERRO: jogador repetido" << std::endl;
    }
    // Caso jogador não exista
    else {
        // Inicializa um novo ponteiro inteligente para o jogador
        std::shared_ptr<Jogador> jogador (new Jogador(apelido, nome));
        // Adiciona o novo jogador ao map de jogadores da jogada
        // O apelido é a chave única e o valor é o ponteiro para o objeto
        this->jogadores[jogador->getApelido()] = std::move(jogador);
        std::cout << "Jogador " << apelido << " cadastrado com sucesso" << std::endl;
    }
}
// Remove um jogador da jogada
void Jogada::removerJogador(std::string apelido, std::string dir_data) {
    // Verifica se existe jogador com o apelido
    auto it =  this->jogadores.find(apelido);
    // Caso exista jogador com o apelido
    if (it != this->jogadores.end()) {
        // Armazena o apelido do jogador
        std::string apelido = it->second->getApelido();
        // Define o caminho para o arquivo com os dados do jogador
        std::string f_jogador = dir_data + "/" + apelido + ".txt";
        // Exclui o arquivo com as estatísticas do jogador
        if (std::filesystem::remove(f_jogador)) {
            // caso arquivo seja excluido: retorna true
            // caso arquivo não exista: retorna false (pode acontecer se jogador for criado e excluido sem que o método salvarJogadores() seja chamado)
        }
        this->jogadores.erase(apelido);
        std::cout << "Jogador " << apelido << " removido com sucesso" << std::endl;

    }
    // Caso o jogador não exista
    else {
        std::cout << "ERRO: jogador inexistente" << std::endl;
    }
}
// Lista as estatísticas de todos os jogadores da jogada
void Jogada::listarJogadores() const {
    // Iterador para percorrer o map de jogadores
    for (const auto& it : this->jogadores) {
        it.second->listarEstatisticas();
    }
}
// Seleciona um jogador da jogada a partir do apelido
Jogador* Jogada::selecionarJogador(std::string apelido) const {
    // Procura o jogador
    auto it =  this->jogadores.find(apelido);
    // Caso o jogador exista
    if (it != this->jogadores.end()) {
        // Retorna um ponteiro para o objeto
        return it->second.get();
    }
    // Caso jogador não exista
    else {
        // Retorna um ponteiro nulo
        return nullptr;
    }
}