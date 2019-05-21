#ifndef LIFE_H
#define LIFE_H

#include <vector>
#include <string>
#include "cell.h"

class Life {
public:
    /// Construtor padrão. Inicializa uma matriz n x m com determinada configuração.
    Life( size_t, size_t, const std::vector< Cell >& );
    /// Destrutor.
    ~Life();
    /// Carregar configuração para a matriz.
    void load( void );
    /// Retorna `true` se a configuração tornou-se extinta, `false` caso contrário.
    bool extinct( void ) const;
    /// Retorna `true` se a configuração tornou-se estável, `false` caso contrário.
    bool stable( void ) const;
    /// Útil para depuração; imprime o conteúdo da matriz.
    void print( void ) const;
private:
    size_t nLin, nCol;          //!< Dimensões da grade.
    size_t born;                //!< Quantidade exata de vizinhos para uma célula passar a viver.
    size_t s1, s2;              //!< Quantidade exata de vizinhos para uma célula sobreviver.
    unsigned short** grade;     //!< Matriz que representa a configuração.
    std::vector< Cell > list;   //!< Lista de células vivas.
    std::vector< std::string > log;  //!< Histórico de gerações.

public:
    //=== Funções utilitárias
    /// Aplica as regras de mudança da configuração.
    void apply_rules( void );
    /// Retorna a quantidade de células vizinhas vivas dada uma posição na grade.
    size_t looking_neighbors( size_t, size_t ) const;
    /// Retorna o índice de uma célula na lista a partir de suas coordenadas.
    size_t cell_at( size_t, size_t ) const;
    /// Adiciona configuração atual ao log.
    void add_config( void );
    /// Útil para depuração; Imprime todos os registros de gerações.
    void show_log( void ) const;
}; // end class

#endif
