#ifndef LIFE_H
#define LIFE_H

#include <vector>
#include <string>

#include "cell.h"

class Life {
public:
    /// Construtor padrão. Inicializa uma matriz n x m com determinada configuração.
    Life( input&& );
    /// Destrutor.
    ~Life();
    /// Aplica as regras de mudança da configuração.
    void update( void );
    /// Imprime a configuração atual na saída padrão.
    void print( void ) const;
    /// Retorna `true` nos seguintes casos:
    /**
     * <ul>
     *  <li> Alcançado o número máximo de gerações;
     *  <li> Configuração tornou-se estável;
     *  <li> Configuração tornou-se extinta.
     * </ul>
     */
    bool conclude( void ) const;
    /// Imprime todos os registros de gerações.
    /**
     * @note Cada registro é composto somente por coordenadas de células vivas.
     */
    void show_log( void ) const;
private:
    size_t nLin, nCol;         //!< Dimensões da grade.
    size_t born;               //!< Quantidade exata de vizinhos para uma célula passar a viver.
    size_t s1, s2;             //!< Quantidade exata de vizinhos para uma célula sobreviver.
    size_t maxgen;             //!< Quantidade máxima de gerações.
    size_t blocksize;          //!< Dimensão do bloco (célula).
    size_t frame_rate;         //!< Taxa de geração por segundo.
    Color cell_color;          //!< Cor da célula.
    Color bckg_color;          //!< Cor do background.
    unsigned short** grade;    //!< Matriz que representa a configuração.
    std::vector< Cell > list;  //!< Lista de células vivas.
    std::vector< std::string > log;  //!< Histórico de gerações.
    //=== Funções utilitárias
    /// Carregar configuração para a matriz.
    void load( void );
    /// Retorna `true` se a configuração tornou-se extinta, `false` caso contrário.
    bool extinct( void ) const;
    /// Retorna `true` se a configuração tornou-se estável, `false` caso contrário.
    bool stable( size_t* ) const;
    /// Retorna a quantidade de células vizinhas vivas dada uma posição na grade.
    size_t looking_neighbors( size_t, size_t ) const;
    /// Retorna o índice de uma célula na lista a partir de suas coordenadas.
    size_t cell_at( size_t, size_t ) const;
    /// Adiciona configuração atual ao log.
    void add_config( void );
}; // end class

#endif
