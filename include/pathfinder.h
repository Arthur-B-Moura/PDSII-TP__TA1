/**
 * @file    pathfinder.h
 * @brief   Declaração das estruturas PathResult e da classe PathFinder.
 *
 * Define o resultado de busca de caminho (PathResult) e a classe PathFinder,
 * responsável por encontrar o menor caminho entre dois nós de um Grafo
 * e converter esse caminho em instruções de navegação legíveis.
 *
 * O algoritmo de busca utilizado é o A* (A-estrela), com a distância haversine
 * como heurística admissível.
 */

#ifndef PATHFINDER_H__
#define PATHFINDER_H__

#include <vector>
#include <unordered_map>
#include <string>
#include "grafo.h"

// ============================================================================= //
//                                    PathResult                                 //
// ============================================================================= //

/**
 * @brief   Encapsula o resultado de uma busca de caminho no grafo.
 *
 * Agrupa a sequência de nós do caminho encontrado, a distância total
 * percorrida e um indicador de sucesso da busca.
 */
struct PathResult {
    /// @brief Sequência ordenada de IDs de nós que compõem o caminho (origem → destino).
    std::vector<long long> node_ids;

    /// @brief Distância total do caminho em metros. Indefinida se @p found for false.
    double total_distance;

    /// @brief Indica se um caminho válido foi encontrado entre os nós fornecidos.
    bool found;
};


// ============================================================================= //
//                                    PathFinder                                 //
// ============================================================================= //

/**
 * @brief   Mecanismo de busca de caminho sobre um Grafo usando o algoritmo A*.
 *
 * PathFinder opera sobre uma referência constante a um Grafo e expõe dois
 * serviços principais: 
 *  
 *  1. find_path()        — encontra o caminho de menor custo entre dois nós.
 * 
 *  2. build_instructions() — converte um PathResult em instruções de navegação
 *                            em linguagem natural.
 */
class PathFinder {
private:
    /// @brief Referência ao grafo sobre o qual as buscas são realizadas.
    const Grafo& grafo_;

    /// ----------------------------------- ///
    /// Métodos auxiliares para uso interno ///
    /// ----------------------------------- ///
    
    /**
     * @brief   Calcula a heurística de distância entre dois nós para o A*.
     *
     * Utiliza a distância haversine entre as coordenadas dos nós como
     * estimativa admissível (nunca superestima o custo real).
     *
     * @param   from_id  ID do nó de origem.
     * @param   to_id    ID do nó de destino.
     * @return  Estimativa de distância em metros entre os dois nós.
     */
    double heuristic(long long from_id, long long to_id) const;

    /**
     * @brief   Calcula o ângulo de direção (bearing) entre dois nós.
     *
     * Retorna o ângulo em graus no sentido horário a partir do norte geográfico,
     * usado para gerar instruções de navegação (ex: "vire à direita").
     *
     * @param   from_id  ID do nó de origem.
     * @param   to_id    ID do nó de destino.
     * @return  Bearing em graus [0.0, 360.0).
     */
    double bearing(long long from_id, long long to_id) const;

    /**
     * @brief   Reconstrói o caminho percorrido a partir do mapa de predecessores.
     *
     * Percorre o mapa @p came_from de trás para frente, partindo de @p end_id
     * até a origem, e retorna a sequência de IDs na ordem correta.
     *
     * @param   came_from  Mapa que associa cada nó ao seu predecessor no caminho ótimo.
     * @param   end_id     ID do nó de destino (ponto de partida da reconstrução).
     * @return  Vetor de IDs de nós ordenado da origem ao destino.
     */
    std::vector<long long> reconstruct_path(
        const std::unordered_map<long long, long long>& came_from,
        long long end_id
    ) const;

public:

    /// ---------------------- ///
    /// Construtor e destrutor ///
    /// ---------------------- ///

    /**
     * @brief   Constrói um PathFinder associado a um Grafo existente.
     * @param   grafo  Grafo sobre o qual as buscas serão realizadas.
     */
    PathFinder(const Grafo& grafo);

    /// @brief Destrutor padrão.
    ~PathFinder();

    /// ----------------- ///
    /// Interface Pública ///
    /// ----------------- ///

    /**
     * @brief   Encontra o caminho de menor custo entre dois nós usando A*.
     *
     * Se um caminho existir, o resultado conterá a sequência de nós e a
     * distância total. Caso contrário, @p found será false e @p node_ids
     * estará vazio.
     *
     * @param   start_id  ID do nó de origem.
     * @param   end_id    ID do nó de destino.
     * @return  PathResult com o caminho encontrado (ou indicação de falha).
     */
    PathResult find_path(long long start_id, long long end_id) const;

    /**
     * @brief   Converte um PathResult em instruções de navegação em texto.
     *
     * Analisa a sequência de nós do resultado e gera uma lista de instruções
     * legíveis (ex: "Siga em frente por 200 m", "Vire à direita na Rua X").
     *
     * @param   result  Resultado de busca previamente obtido por find_path().
     * @return  Vetor de strings com as instruções de navegação em ordem.
     */
    std::vector<std::string> build_instructions(const PathResult& result) const;
};

#endif // PATHFINDER_H__
