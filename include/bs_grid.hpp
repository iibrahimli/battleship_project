/*!
    A game grid for battleship
*/

#ifndef BS_GRID_HPP
#define BS_GRID_HPP

#include <iostream>
#include <map>
#include "exceptions.hpp"

/*!
    @brief Engine namespace

    Namespace containing all classes related to the engine
*/
namespace bship{
    
    /// Cell state
    enum cell_state : uint8_t {
        CL_EMPTY,     ///< the cell has no ship placed, can be targeted
        CL_FULL,      ///< the cell contains a part of a ship
        CL_MISSED,    ///< the cell was EMPTY, but has been hit
        CL_DESTROYED  ///< the cell was FULL, but has been hit
    };
    

    /// Type of ship
    enum ship_type : uint8_t {
        ST_ONE,       ///< one-cell ship
        ST_TWO,       ///< two-cell ship
        ST_THREE,     ///< three-cell ship
        ST_FOUR       ///< four-cell ship
    };


    /// Orientation of ship
    enum ship_orientation : bool {
        SO_HOR,       ///< horizontal
        SO_VERT       ///< vertical
    };
    

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
    cell_state state   = CL_EMPTY;   ///< state of the cell
    int        ship_id = -1;         ///< id of ship covering the cell
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
        if(row >= _height || col >= _width)
            throw index_exception(row, col, "Index out of bound: ");

        return _data[row*_width + col];
    }


    /*!
        @brief Ship placement

        Checks provided placement coordinates and places the ship on the board
        if possible

        @param row, col Coordinates of left- and upper-most cell of the ship
        @param orient Orientation of the ship (SO_HOR or SO_VER)
        @return false if its impossible to place the ship at the 
                given configuration, true otherwise
    */
    bool place_ship(ship_type type, size_t row, size_t col, ship_orientation orient){
        return true;
    }


private:
    size_t                        _width;    ///< width of the grid
    size_t                        _height;   ///< height of the grid
    cell                         *_data;     ///< actual cells of the grid
    std::map<ship_type, uint8_t>  _n_ships;  ///< number of ships of each type

};


#endif