#include <iostream>    // std::cout
#include <functional>  // std::function
#include <sstream>     // std::ostringstream
#include <cstdlib>     // std::system

#include "include/valid.h"
#include "include/stream.h"
#include "include/life.h"
#include "include/initial.h"

/// Constructor
Life::Life( input&& i )
    : nLin{ i.h }, nCol{ i.w }, list{ i.alives }, born{ i.born }, s1{ i.s1 }, s2{ i.s2 }
{
    grade = new unsigned short*[ nLin ];

    for ( size_t i = 0; i < nLin; ++i )
        grade[ i ] = new unsigned short[ nCol ]{ 0 };

    maxgen = get_maxgen();
    blocksize = get_blocksize();
    frame_rate = get_fps();
    cell_color = get_aliveColor();
    bckg_color = get_bkgColor();    

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
{ return ( list.size() == 0 ? true : false ); }

/// Retorna `true` se a configuração tornou-se estável, `false` caso contrário.
bool Life::stable( size_t* count ) const
{
    std::ostringstream oss;

    for ( const Cell& c : list )
        oss << c << ' ';

    *count = 1;

    for ( const auto& s : log )
    {
        if ( s == oss.str() )
            return true;

        ++( *count );
    } // end for
    
    return false;
}

/// Retorna `true` nos seguintes casos:
/**
 * <ul>
 *  <li> Alcançado o número máximo de gerações;
 *  <li> Configuração tornou-se estável;
 *  <li> Configuração tornou-se extinta.
 * </ul>
 */
bool Life::conclude( void ) const
{
    static size_t generations = 0;
    size_t aux;
    bool flag;
    
    if ( ( flag = extinct() ) )
        std::cout << "\nConfiguração " << ( log.size() ) << " tornou-se extinta.\n";
    else if ( ( flag = stable( &aux ) ) )
        std::cout << "\nConfiguração " << ( log.size() + 1 )
            << " tornou-se estável. N = " << aux << ".\n";
    else if ( !is_maxgen()  && ( flag = ( generations >= maxgen ? true : false ) ) )
        std::cout << "\nAtingido o número máximo de gerações.\n";

    ++generations;

    return flag;    
}

/// Imprime a configuração atual
void Life::print( void ) const
{
    static size_t count = 1;
    static size_t frames = 1;

    std::cout << "Generation " << count++ << ":\n";

    for ( size_t i = 0; i < nLin; ++i )
    {
        std::cout << "[ ";

        for ( size_t j = 0; j < nCol; ++j )
            std::cout << ( grade[ i ][ j ] ? '*' : ' ' );

        std::cout << " ]\n";
    } // end outer for

    if ( frames == frame_rate )
    {
        frames = 1;
        std::system( "sleep 1");
    }
    else
        ++frames;
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
void Life::update( void )
{
    // Passo 1: Adicionar configuração anterior ao log de gerações.
    add_config();

    // Passo 2: Aplicar as regras de nascimento e sobrevivência.
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

    // Passo 3: Remover células mortas da configuração.
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

    // Passo 4: Carregar nova configuração para a matriz.
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

/// Imprime todos os registros de gerações.
void Life::show_log( void ) const
{
    std::cout << "\n>>> Log de gerações:\n====================\n";

    for ( const auto& s : log )
        std::cout << s << '\n';
}

int main( int argc, char** argv )
{
    valid_arguments( argc, argv );
    

    if ( is_valid() )
    {
        std::string input_file = get_input_dir();
        print_initial_msg();

        Life gen( readFile( input_file ) );

        while ( not gen.conclude() )
        {
            gen.print();
            gen.update();
        }
    }
    
    return 0;
} // end main
