/*!
    A game grid for battleship
*/

#ifndef BS_GRID_HPP
#define BS_GRID_HPP

#include <iostream>
#include "exceptions.hpp"

/*!
    @brief Engine namespace

    Namespace containing all classes related to the engine
*/
namespace bship{
    /*!
        EMPTY:      the cell has no ship placed, can be targeted
        FULL:       the cell contains a part of a ship
        MISSED:     the cell was EMPTY, but has been hit
        DESTROYED:  the cell was FULL, but has been hit
    */
    enum cell_state : uint8_t { CL_EMPTY, CL_FULL, CL_MISSED, CL_DESTROYED };
    
    /*!
        SH_ONE:     [_]          SH_TWO:     [_|_]

        SH_THREE:   [_|_|_]      SH_FOUR:    [_|_|_|_]
    */
    enum ship_type : uint8_t { SH_ONE, SH_TWO, SH_THREE, SH_FOUR };

    /// orientation of ship (needed when placing a ship)
    enum ship_orientation : bool { SR_HOR, SR_VERT };
    
    struct cell;
    class bs_grid;
}



/*!
    @brief Grid cell

    A grid cell holding data about itself
    basic element of a grid, since a 'ship'
    entity was not deemed worthy of existence
*/
struct bship::cell{
    cell_state state   = CL_EMPTY;
    int        ship_id = -1;
};



/*!
    @class bs_grid

    @brief A battleship game grid

    The game grid contains all state information about
    current game related to its associated player
*/
class bship::bs_grid{
public:

    /*!
        @brief bs_grid constructor

        Constructs a grid of given size

        @param width Width of the grid (x dimension)
        @param height Height of the grid (y dimension)
    */
    bs_grid(size_t width, size_t height)
    :   _width(width),
        _height(height)
    {
        _data = new cell[_width * _height];
    }


    ~bs_grid(){
        delete[] _data;
    }

    /// Getter for width
    size_t width() const { return _width; }


    /// Getter for height
    size_t height() const { return _height; }


    /*!
        @brief Cell access

        Easy cell access
        (cells are stored in row-major order)

        @param row Row number of requested cell
        @param col Column number of requested cell
        @return Reference to the requested cell
    */
    inline cell& cell_at(size_t row, size_t col){
        if(row >= _height || col >= _width) throw index_exception();
        return _data[row*_width + col];
    }


    // (row, col) is the left- and upper-most cell of the ship
    // returns false if its impossible to place the ship at the 
    // given location, true otherwise
    bool place_ship(ship_type type, size_t row, size_t col, ship_orientation ornt){
        return true;
    }


private:
    size_t    _width;       ///< width of the grid
    size_t    _height;      ///< height of the grid
    cell     *_data;        ///< actual cells of the grid
    uint8_t   _n_ships[4];  ///< number of ships of each type

};


#endif