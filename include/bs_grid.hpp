/*!
    A game grid for battleship
*/

#ifndef BS_GRID_HPP
#define BS_GRID_HPP

#include <iostream>
#include <map>
#include <vector>
#include "exceptions.hpp"

/*!
    @brief Engine namespace

    Namespace containing all classes related to the engine
*/
namespace bship{
    
    /// Cell state
    enum cell_state : uint8_t {
        CS_EMPTY,     ///< the cell has no ship placed, can be targeted
        CS_FULL,      ///< the cell contains a part of a ship
        CS_MISSED,    ///< the cell was EMPTY, but has been hit
        CS_DESTROYED  ///< the cell was FULL, but has been hit
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
    std::ostream& operator<<(std::ostream& os, bs_grid& grid);
}



/*!
    @brief Grid cell

    A grid cell holding data about itself
    basic element of a grid, since a 'ship'
    entity was not deemed worthy of existence
*/
struct bship::cell{

    cell_state state   = CS_EMPTY;   ///< state of the cell
    int        ship_id = -1;         ///< id of ship covering the cell


    /*!
        @brief Check if ship part can be placed

        @return true if cell is empty, false otherwise
    */
    inline bool can_place(){
        return (state == CS_EMPTY);
    }


    /*!
        @brief Check if cell can be hit

        @return true if cell has not been hit yet, false otherwise
    */
    inline bool can_target(){
        return (state == CS_EMPTY || state == CS_FULL);
    }
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
        _height(height),
        _ready(false)
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

        @param row, col Coordinates of requested cell
        @return Reference to the requested cell
    */
    inline cell& cell_at(size_t row, size_t col){
        if(row >= _height || col >= _width)
            throw index_exception(row, col, "Index out of bounds: ");

        return _data[row*_width + col];
    }


    /*!
        @brief Ship placement

        Checks provided placement coordinates and places the ship on the board
        if possible

        @param type Type of ship to be placed (example: ST_TWO)
        @param row, col Coordinates of left- and upper-most cell of the ship
        @param orient Orientation of the ship (SO_HOR or SO_VER)
        @return false if its impossible to place the ship at the 
                given configuration, true otherwise
    */
    bool place_ship(ship_type type, size_t row, size_t col, ship_orientation orient){

        // if board is fully populated
        if(_ready) throw illegal_move_exception("All ships already placed");



        return true;
    }


    friend std::ostream& operator<<(std::ostream& os, bship::bs_grid& grid);


private:
    size_t                        _width;    ///< width of the grid
    size_t                        _height;   ///< height of the grid
    cell                         *_data;     ///< actual cells of the grid
    std::map<ship_type, uint8_t>  _n_ships;  ///< number of ships of each type
    bool                          _ready;    ///< true if all available ships are placed

};



/*!
    @brief Prints the grid

    Overloaded operator << to print the grid to an output stream

    @param os Reference to output stream to print to
    @param grid Reference to a bs_grid object
    @return Reference to the stream
*/
std::ostream& bship::operator<<(std::ostream& os, bship::bs_grid& grid){

    // print top line
    os << " ";
    for(size_t i=0; i<grid._width*3; ++i) os << "_";
    os << std::endl;

    // print cells
    for(size_t r=0; r<grid._height; ++r){
        os << "|";
        for(size_t c=0; c<grid._width; ++c){
            switch(grid.cell_at(r, c).state){
                case CS_EMPTY:
                    os << "__";
                    break;
                case CS_FULL:
                    os << "██";
                    break;
                case CS_MISSED:
                    os << "×_";
                    break;
                case CS_DESTROYED:
                    // os << "░░";
                    os << "╬╬";
                    break;
            }
            os << "|";
        }
        // os << "|" << std::endl;
        os << std::endl;
    }
    // os << " ";
    // for(size_t i=0; i<grid._width*3; ++i) os << "¯";
    // os << std::endl;

    return os;
}



#endif