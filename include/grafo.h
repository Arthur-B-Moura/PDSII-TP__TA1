/**
 * @file    grafo.h
 * @brief   Declaração das estruturas Edge e Grafo para representação de grafos de navegação.
 *
 * Define a estrutura de aresta (Edge) e a classe Grafo, que modela um grafo
 * ponderado não-direcionado de nós geográficos (MapNode). As arestas são
 * ponderadas pela distância haversine entre os nós conectados.
 */

#ifndef GRAFO_H__
#define GRAFO_H__

#include <vector>
#include <unordered_map>
#include "map_node.h"


// ============================================================================= //
//                                    Edge                                       //
// ============================================================================= //

/**
 * @brief   Representa uma aresta direcionada no grafo.
 *
 * Armazena o nó de destino e o custo (distância em km) para percorrer
 * essa aresta a partir de um nó de origem implícito na lista de adjacência.
 */
struct Edge {
    long long   toNodeId;
    double      distance;

    /**
     * @brief   Compara duas arestas por igualdade.
     * @param   b  Aresta a ser comparada com a atual.
     * @return  true se ambas apontam para o mesmo nó com a mesma distância, false caso contrário.
     */
    bool operator==(Edge b) {
        return ((this->toNodeId == b.toNodeId) && (this->distance == b.distance));
    }
};


// ============================================================================= //
//                                    Grafo                                      //
// ============================================================================= //

/**
 * @brief   Grafo ponderado de nós geográficos com lista de adjacência.
 *
 * Modela uma rede de navegação onde cada vértice é um MapNode e cada aresta
 * carrega a distância haversine (em quilômetros) entre os dois nós conectados.
 * A estrutura interna usa mapas de hash para acesso O(1) a nós e vizinhos.
 */
class Grafo {
protected:
    /// @brief Conjunto de nós do grafo, indexados pelo seu ID.
    std::unordered_map<long long, MapNode> nodes_;
    
    /// @brief Lista de adjacência: mapeia o ID de cada nó ao vetor de suas arestas de saída.
    std::unordered_map<long long, std::vector<Edge>> adjacency_;

    /// @brief Contador do número total de arestas no grafo.
    int edge_count_;

    // ----------------------------------- //
    // Métodos auxiliares para uso interno //
    // ----------------------------------- //

    /**
     * @brief   Calcula a distância haversine entre dois nós geográficos.
     *
     * A fórmula haversine considera a curvatura da Terra e retorna a distância
     * em quilômetros entre as coordenadas dos dois nós fornecidos.
     *
     * @param   a  Nó de origem.
     * @param   b  Nó de destino.
     * @return  Distância em quilometros entre @p a e @p b.
     */
    double haversine_distance(const MapNode& a, const MapNode& b) const;

    /**
     * @brief   Verifica se uma aresta já existe em um vetor de arestas.
     *
     * Usado internamente para evitar arestas duplicadas na lista de adjacência.
     *
     * @param   haystack  Vetor de arestas onde a busca será realizada.
     * @param   needle    Aresta a ser procurada.
     * @return  true se @p needle for encontrada em @p haystack.
     */
    bool edge_exists(std::vector<Edge> haystack, Edge needle) const;

public:
    // ---------------------- //
    // Construtor e destrutor //
    // ---------------------- //
    
    /// @brief Constrói um grafo vazio.
    Grafo();

    /// @brief Destrutor padrão para Grafo.
    ~Grafo();

    // --------------------------------------- //
    // Mutadores - modificam o estado do grafo //
    // --------------------------------------- //
    
    /**
     * @brief   Adiciona um nó ao grafo.
     *
     * Se um nó com o mesmo ID já existir, a operação é ignorada.
     *
     * @param   node  Nó a ser inserido.
     */
    void add_node(const MapNode& node);
    
    /**
     * @brief   Adiciona uma aresta bidirecional (TODO: FIX) entre dois nós.
     *
     * A distância da aresta é calculada automaticamente via haversine.
     * Nenhuma aresta duplicada é inserida.
     * @throws std::invalid_argument Se tentar ligar nós cujos ids não estão registrados
     * 
     * @param   from_id  ID do nó de origem.
     * @param   to_id    ID do nó de destino.
     */
    void add_edge(long long from_id, long long to_id);

    /**
     * @brief   Adiciona arestas bidirecionais de um nó para vários outros.
     *
     * Equivale a chamar add_edge(from_id, id) para cada ID em @p ids_connected_to.
     * @throws std::invalid_argument Se tentar ligar nós cujos ids não estão registrados
     *
     * @param   from_id           ID do nó de origem.
     * @param   ids_connected_to  Lista de IDs dos nós de destino.
     */
    void add_edge(long long from_id, std::vector<long long> ids_connected_to);

    // --------------------------------------- ///
    // Acessores - leitura do estado do grafo  //
    // --------------------------------------- //
    
    /**
     * @brief   Retorna uma referência constante ao nó com o ID fornecido.
     *
     * @param   id  ID do nó desejado.
     * @return  Referência constante ao MapNode correspondente.
     * @throws  std::invalid_argument Se nenhum nó com esse ID existir.
     */
    const MapNode& get_node(long long id) const;
    
    /**
     * @brief   Retorna o vetor de arestas de saída de um nó.
     *
     * @param   node_id  ID do nó cujos vizinhos se deseja obter.
     * @return  Referência constante ao vetor de Edge associado ao nó.
     * @throws  std::invalid_argument Se o nó não existir no grafo.
     */
    const std::vector<Edge>& get_neighbors(long long node_id) const;

    /**
     * @brief   Verifica se um nó com o ID fornecido existe no grafo.
     * @param   id  ID a ser verificado.
     * @return  true se o nó existir.
     */
    bool has_node(long long id) const;

    /**
     * @brief   Retorna o número de nós (vértices) no grafo.
     * @return  Quantidade de nós atualmente armazenados.
     */
    int node_count() const;

    /**
     * @brief   Retorna o número total de arestas no grafo.
     * @return  Valor atual de edge_count_.
     */
    int edge_count() const;
};

#endif // GRAFO_H__