#include <iostream>
#include <cstdlib>

// LIFE CLASS AREA
//===================================================================================
#include <functional> // std::function
#include <sstream>    // std::ostringstream
#include "life.h"

/// Constructor
Life::Life( size_t lin, size_t col, const std::vector< Cell >& other )
    : nLin{ lin }, nCol{ col }, list{ other }
{
    grade = new unsigned short*[ nLin ];

    for ( size_t i = 0; i < nLin; ++i )
        grade[ i ] = new unsigned short[ nCol ]{ 0 };

    born = 3;   // Atualmente Default
    s1 = 2;     // Atualmente Default
    s2 = 3;     // Atualmente Default

    add_config();
    load();
}

/// Destructor
Life::~Life()
{
    for ( size_t i = 0; i < nLin; ++i )
        delete[] grade[ i ];

    delete[] grade;
}

/// Carregar configuração para a matriz.
void Life::load( void )
{
    for ( size_t cell = 0 ; cell < list.size() ; ++cell )
        grade[ list[ cell ].getX() ][ list[ cell ].getY() ] = 1;
}

/// Retorna `true` se a configuração tornou-se extinta, `false` caso contrário.
bool Life::extinct( void ) const
{
    if ( list.size() == 0 )
    {
        std::cout << "Configuração " << ( log.size() ) << " tornou-se extinta.\n";
        return true;
    }
    
    return false;
}

/// Retorna `true` se a configuração tornou-se estável, `false` caso contrário.
bool Life::stable( void ) const
{
    std::ostringstream oss;

    for ( const Cell& c : list )
        oss << c << ' ';

    size_t count = 1;

    for ( const auto& s : log )
    {
        if ( s == oss.str() )
        {   
            std::cout << "Configuração " << ( log.size() + 1 )
                    << " tornou-se estável.\nN = " << count << '\n';
            return true;
        }

        ++count;
    } // end for
        
    return false;
}

/// Útil para depuração
void Life::print( void ) const
{
    for ( size_t i = 0; i < nLin; ++i )
    {
        std::cout << '[';

        for ( size_t j = 0; j < nCol; ++j )
            std::cout << ' ' << ( grade[ i ][ j ] ? '*' : ' ' );

        std::cout << " ]\n";
    } // end outer for

    std::system( "sleep 1");
}

/// Retorna a quantidade de células vizinhas vivas.
size_t Life::looking_neighbors( size_t x, size_t y ) const
{
    size_t nLin = Life::nLin;
    size_t nCol = Life::nCol;
    size_t count = 0;
    // Verifica se um par de coordenadas está dentro dos limites da grade.
    std::function< bool (size_t,size_t) > inside = [ nLin, nCol ]( size_t x, size_t y )->bool
    { return ( x >= 0 ) && ( x < nLin ) && ( y >= 0 ) && ( y < nCol ); };

    inside( x - 1, y - 1 ) ? ( grade[ x - 1 ][ y - 1 ] ? count += 1 : 0 ) : 0;
    inside( x - 1, y + 1 ) ? ( grade[ x - 1 ][ y + 1 ] ? count += 1 : 0 ) : 0;
    inside( x + 1, y - 1 ) ? ( grade[ x + 1 ][ y - 1 ] ? count += 1 : 0 ) : 0;
    inside( x + 1, y + 1 ) ? ( grade[ x + 1 ][ y + 1 ] ? count += 1 : 0 ) : 0;
    inside( x, y - 1 ) ? ( grade[ x ][ y - 1 ] ? count += 1 : 0 ) : 0;
    inside( x, y + 1 ) ? ( grade[ x ][ y + 1 ] ? count += 1 : 0 ) : 0;
    inside( x - 1, y ) ? ( grade[ x - 1 ][ y ] ? count += 1 : 0 ) : 0;
    inside( x + 1, y ) ? ( grade[ x + 1 ][ y ] ? count += 1 : 0 ) : 0;

    return count;
}

/// Retorna o índice de uma célula na lista a partir de suas coordenadas.
size_t Life::cell_at( size_t x, size_t y ) const
{   
    size_t idx;
    for ( size_t i = 0 ; i < list.size(); ++i )
        if ( list[ i ].exists( x , y ) )
            idx = i;

    return idx;
}

/// Aplica as regras de mudança da configuração.
void Life::apply_rules( void )
{
    // Passo 1: Aplicar as regras de nascimento e sobrevivência.
    for ( size_t i = 0 ; i < nLin ; ++i )
    {
        for (size_t j = 0 ; j < nCol ; ++j )
        {
            size_t count = looking_neighbors( i, j );
            bool alive = grade[ i ][ j ];

            if ( alive && count != s1 && count != s2 ) // Célula viva não sobrevive
                list[ cell_at( i, j ) ].setStatus( false );
            else if ( !alive && count == born ) // Célula nasce
                list.push_back( Cell(i,j) );
        } // end inner for
    } // end outer for

    // Passo 2: Remover células mortas da configuração.
    for ( auto it = list.begin(); it != list.end(); )
    {
        if ( !it->getStatus() )
        {
            grade[ it->getX() ][ it->getY() ] = 0;
            it = list.erase( it );
        } // end if
        else
            ++it;
    } // end for

    list.shrink_to_fit();

    // Passo 3: Carregar nova configuração para a matriz.
    load();
}

/// Adiciona configuração atual ao log.
void Life::add_config( void )
{
    std::ostringstream oss;

    for ( const Cell& c : list )
        oss << c << ' ';

    log.push_back( oss.str() );
}

/// Útil para depuração; Imprime todos os registros de gerações.
void Life::show_log( void ) const
{
    std::cout << "\n>>> Log de gerações:\n====================\n";

    for ( const auto& s : log )
        std::cout << s << '\n';
}
//===================================================================================


int main( void )
{
    // Simulação de baixo nível: Recebendo dados do arquivo de configuração.
    // Ao cerregar os dados de entrada, a lista de células deve ser inicializada
    // com as informações de todas as células vivas. Como por exemplo, o vector v
    // foi inicializado a partir da seguinte configuração:
    // ..........
    // ..**.....*
    // .........*
    // ....***..*
    // ....***...
    // ..........
    // ..........
    // ..........
    // ..........
    // ..........
    const std::vector<Cell> v{ Cell(0,0), Cell(0,1), Cell(0,2), Cell(1,1) };

    Life gen( 10, 10, v );

    // TODO: Game loop
    gen.print(); std::cout << '\n';

    while ( true )
    {
        gen.apply_rules();
        gen.print(); std::cout << '\n';
        if ( gen.stable() ) break;
        if ( gen.extinct() ) break;
        gen.add_config();
    }

    gen.show_log();

    return 0;
} // end main
