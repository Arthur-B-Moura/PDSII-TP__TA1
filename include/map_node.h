/**
 * @file    map_node.h
 * @brief   Declaração da classe MapNode, representando um nó do mapa com um identificador único e uma posição geográfica.
 * 
 * A classe MapNode encapsula as informações de um nó do mapa, incluindo seu identificador (id) e sua posição geográfica (latitude e longitude). 
 * A classe também inclui uma estrutura auxiliar Coordenada para representar a posição geográfica de forma clara e organizada.
 * 
 * A implementação da classe MapNode inclui validação para garantir que as coordenadas fornecidas sejam válidas, lançando exceções quando necessário.
 */

#ifndef MAP_NODE_H__
#define MAP_NODE_H__

#include <string>
#include <vector>


// ============================================================================= //
//                                    Coordenada                                 //
// ============================================================================= //

/**
 * @brief   Representa uma coordenada geográfica, com latitude e longitude. 
 */
struct Coordenada {
    double latitude_;
    double longitude_;

    /// @brief Verifica se a coordenada geográfica é válida (dentro dos limites de latitude e longitude)
    /// @return true se a coordenada for válida, false caso contrário
    bool isValid() const;
};


// ============================================================================= //
//                                    MapNode                                    //
// ============================================================================= //


/**
 * @brief   Representa um nó do mapa, com um identificador único e uma posição geográfica.
 */
class MapNode {
private:
    long long int id_;
    Coordenada posicao_;
    
public:
    /**
     * @brief   Constrói um MapNode a partir de seu id e posição geográfica.
     * @pre     Valor de id deve ser válido (único e não negativo).
     *
     * @param   id   Identificador único do nó (por exemplo, o id osm).
     * @param   pos  Coordenada geográfica do nó.
     *
     * @throws  std::invalid_argument Se a coordenada fornecida for inválida
     *          (fora dos limites de latitude ou longitude).
     */
    MapNode(const long long int id, Coordenada pos);
    
    /// @brief Descrutor padrão de MapNode
    ~MapNode();

    /**
     * @brief   Retorna a posição geográfica do nó.
     * @return  obj Coordenada associada ao nó.
     */
    Coordenada posicao() const;
    
    /**
     * @brief   Retorna o identificador do nó.
     * @return  ID do nó como long long int.
     */
    long long int id() const;
};

#endif