#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <ostream>
#include <vector>

class Cell {
private:
    size_t x, y; //!< Coordenadas cartesianas.
    bool alive; //!< Estado da célula.
public:
    /// Default Constructor
    Cell( size_t x_, size_t y_, bool live = true ) : x{ x_ }, y{ y_ }, alive{ live }
    {/* empty */}

    /// Add info
    size_t getX( void ) const { return x; }
    /// Add info
    size_t getY( void ) const { return y; }
    /// Add info
    bool getStatus( void ) const { return alive; }
    /// Add info
    void setStatus( bool st ) { alive = st; }
    /// Útil para depuração
    friend std::ostream& operator<<( std::ostream& os, const Cell& c )
    {
        os << "(" << c.getX() << "," << c.getY() << ") = " << ( c.getStatus() ? "alive" : "dead" );
        return os;
    }
    bool operator==(Cell &c){
        return (x == c.x && y == c.y && alive == c.alive);
    }
    bool exists(size_t _x,size_t _y){
        return (x == _x && y == _y);
    }
};
#endif