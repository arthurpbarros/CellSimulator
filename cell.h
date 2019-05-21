#ifndef CELL_H
#define CELL_H

#include <ostream>

class Cell {
private:
    size_t x, y; //!< Coordenadas cartesianas.
    bool alive; //!< Estado da célula.
public:
    /// Default Constructor
    Cell( size_t x, size_t y, bool live = true ) : x{ x }, y{ y }, alive{ live }
    {/* empty */}

    /// Add info
    size_t getX( void ) const { return x; }
    /// Add info
    size_t getY( void ) const { return y; }
    /// Add info
    bool getStatus( void ) const { return alive; }
    /// Add info
    void setStatus( bool st ) { alive = st; }
    /// Add info
    bool exists( size_t x, size_t y ) const { return ( Cell::x == x && Cell::y == y ); }
    /// Add info
    friend std::ostream& operator<<( std::ostream& os, const Cell& c )
    {
        os << '(' << c.getX() << ',' << c.getY() << ')';
        return os;
    }
};
#endif
