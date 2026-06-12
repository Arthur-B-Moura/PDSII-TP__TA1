#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include "map.h"
#include "map_generator.h"
#include "pathfinder.h"
#include "map_node.h"
#include "grafo.h"

int main() {
    // Inicialização e carregamento do mapa
    MapGenerator gerador("maps/map_liberdade.osm");
    Map& mapa = gerador.get_mapa();

    // Avisa ao usuário caso algo tenha dado errrado na criação do mapa
    if (mapa.nome() == "empty_map") {
        std::cerr << "Erro ao carregar o arquivo de mapa!" << std::endl;
        return 1;
    }

    // Inicialização do dicionário de estruturas
    const auto& estruturas = mapa.dict_estruturas();

    // Declaração de variáveis para os inputs do usuário
    std::string ponto_partida = "Não definido";
    std::string ponto_destino = "Não definido";
    int opcao = 0;

    // Loop do menu principal
    while (opcao != 4){
        std::cout << "\n========================================" << std::endl;
        std::cout << "         SISTEMA DE NAVEGAÇÃO           " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << " Partida: " << ponto_partida << std::endl;
        std::cout << " Destino: " << ponto_destino << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "[1] Adicionar/trocar ponto de partida" << std::endl;
        std::cout << "[2] Adicionar/trocar ponto de destino" << std::endl;
        std::cout << "[3] Iniciar viagem" << std::endl;
        std::cout << "[4] Cancelar viagem e fechar o sistema" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Escolha uma opção: ";
        
        // Captura a opção do usuário
        if (!(std::cin >> opcao)) {
            std::cout << "\nErro: Entrada inválida! Digite apenas números." << std::endl;

            // Barricada: limpa o estado de erro do cin
            std::cin.clear();
            // std::numeric_limits<std::streamsize>::max() é o tamanho máximo possível do buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue; // Reinicia o menu
}
        // Limpa o buffer de entrada para evitar problemas com getline
        std::cin.ignore(1000, '\n');

        // Avalia a opção selecionada e a execute de acordo
        switch (opcao) {
            case 1:{
                std::cout << "Digite o novo ponto de partida (Insira um ponto inválido para apagar o ponto de partida atual): ";

                // Captura a entrada do usuário para o ponto de partida
                std::getline(std::cin, ponto_partida);

                bool encontrado = false;

                // Procura pelo ponto no dicionário de estruturas e valida a entrada
                for (auto const& [id, lugar] : estruturas){
                    if (lugar.nome == ponto_partida){
                        std::cout << "Ponto de partida definido: " << lugar.nome << std::endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Ponto de partida não encontrado, tente novamente!" << std::endl;
                    ponto_partida = "Não definido";
                }
                break;
            }
            case 2:{
                std::cout << "Digite o novo ponto de destino: ";

                // Captura a entrada do usuário para o ponto de destino
                std::getline(std::cin, ponto_destino);

                bool encontrado = false;

                // Procura pelo ponto no dicionário de estruturas e valida a entrada
                for (auto const& [id, lugar] : estruturas){
                    if (lugar.nome == ponto_destino){
                        std::cout << "Ponto de destino definido: " << lugar.nome << std::endl;
                        encontrado = true;
                        if (ponto_partida == ponto_destino) {
                            std::cout << "Ponto de partida e destino são iguais! Por favor, escolha um destino diferente." << std::endl;
                            ponto_destino = "Não definido";
                            break;
                        }
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Ponto de destino não encontrado, tente novamente!" << std::endl;
                    ponto_destino = "Não definido";
                }
                break;
            }

            case 3:{
                if (ponto_partida == "Não definido" || ponto_destino == "Não definido") {
                    std::cout << "Por favor, defina tanto o ponto de partida quanto o ponto de destino antes de iniciar a viagem!" << std::endl;
                    break;
                }

                std::cout << "Calculando rota e iniciando viagem..." << std::endl;
                
                // Localiza os IDs dos nós de início e fim
                long long id_partida = -1;
                long long id_destino = -1;

                for (auto const& [id_estrutura, lugar] : estruturas) {
                    // Verifica se o nome corresponde e se a estrutura possui nós associados
                    if (lugar.nome == ponto_partida && !lugar.nodes_id_ref.empty()){
                        id_partida = lugar.nodes_id_ref.at(0);
                    }
                    if (lugar.nome == ponto_destino && !lugar.nodes_id_ref.empty()){
                        id_destino = lugar.nodes_id_ref.at(0);
                    }
                }

                // Só prossegue se ambos os IDs dos nós foram encontrados no grafo
                if (id_partida != -1 && id_destino != -1) {
                    PathFinder pf(mapa);
                    // O algoritmo A* retorna um objeto PathResult [3]
                    PathResult resultado = pf.find_path(id_partida, id_destino);

                    if (resultado.found) {
                        std::cout << "\n========================================" << std::endl;
                        std::cout << " ROTA ENCONTRADA COM SUCESSO!" << std::endl;
                        // total_distance contém a distância acumulada em metros
                        std::cout << " Distância total estimada: " << resultado.total_distance * 1000 << " metros." << std::endl;
                        std::cout << "========================================\n" << std::endl;

                        // Gera o vetor de instruções a serem seguidas
                        std::vector<std::string> instrucoes = pf.build_instructions(resultado);
                        
                        // Looping para a exibição das instruções
                        int escolha;
                        size_t i;
                        for(i = 0; i < instrucoes.size(); i++){
                            std::cout << instrucoes[i] << std::endl;

                            std::cout << "Escolha [0] para cancelar a viagem ou [1] caso tenha concluído a última etapa do percurso e queira continuar: " << std::endl;
                            // Tenta caputrar escolha
                            if(!(std::cin >> escolha)) {
                                // Trata caso de não número
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Erro: Entrada inválida! Digite apenas 0 ou 1." << std::endl;
                                i--; continue; // Repete a instrução atual
                            }
                            if(escolha == 0){
                                std::cout << "Muito bem, viagem cancelada.\n" << std::endl;
                                break;
                            }else if(escolha == 1){
                                std::cout << "Perfeito, continuando.\n" << std::endl;
                            }else{
                                std::cout << "Erro: entrada inválida! Digite apenas 0 ou 1." << std::endl;
                            }


                        }

                        // Reseta ponto_partida e ponto_destino para uma próxima viagem
                        ponto_destino = "Não definido";
                        ponto_partida = "Não definido";
                    }else{
                        std::cout << "Erro: Não foi possível traçar um caminho entre esses pontos." << std::endl;
                    }
                }else{
                    std::cout << "Erro: Um ou ambos os endereços não possuem pontos de acesso válidos." << std::endl;
                }

                break;
            }
            case 4:
                // Encerra o sistema
                std::cout << "Viagem cancelada. Encerrando o sistema." << std::endl;
                break;

            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
                break;
        }
    }

    return 0;
}
