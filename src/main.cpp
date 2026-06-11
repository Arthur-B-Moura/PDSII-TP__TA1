#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "map.h"
#include "map_generator.h"

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
    std::string endereco_partida = "Não definido";
    std::string endereco_destino = "Não definido";
    int opcao = 0;

    // Loop do menu principal
    while (opcao != 4){
        std::cout << "\n========================================" << std::endl;
        std::cout << "         SISTEMA DE NAVEGAÇÃO           " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << " Partida: " << endereco_partida << std::endl;
        std::cout << " Destino: " << endereco_destino << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "[1] Adicionar/trocar endereço de partida" << std::endl;
        std::cout << "[2] Adicionar/trocar endereço de destino" << std::endl;
        std::cout << "[3] Iniciar viagem" << std::endl;
        std::cout << "[4] Cancelar viagem e fechar o sistema" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Escolha uma opção: ";
        
        // Captura a opção do usuário
        std::cin >> opcao;

        // Limpa o buffer de entrada para evitar problemas com getline
        std::cin.ignore(1000, '\n');

        // Avalia a opção selecionada e a execute de acordo
        switch (opcao) {
            case 1:
                std::cout << "Digite o novo endereço de partida: ";

                // Captura a entrada do usuário para o endereço de partida
                std::getline(std::cin, endereco_partida);

                // Procura pelo endereço no dicionário de estruturas e valida a entrada
                
                break;

            case 2:
                std::cout << "Digite o novo endereço de destino: ";

                // Captura a entrada do usuário para o endereço de destino
                std::getline(std::cin, endereco_destino);

                // Procura pelo endereço no dicionário de estruturas e valida a entrada

                break;

            case 3:
                std::cout << "Calculando rota e iniciando viagem..." << std::endl;
                // Aqui entrará o algoritmo A*
                break;

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
