/*!
    A game grid for battleship
*/

#ifndef BS_GRID_HPP
#define BS_GRID_HPP


#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "exceptions.hpp"


// for small printing - uncomment for regular ASCII printing
#define SMALL_PRINT


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
    

    /// Type (and size, kinda) of ship (underlying value shows the size of ship) (MODIFY if necessary)
    enum ship_type : uint8_t {
        ST_TWO=2,     ///< two-cell ship
        ST_THREE,     ///< three-cell ship
        ST_FOUR,      ///< four-cell ship
        ST_FIVE       ///< five-cell ship
    };


    /// Orientation of ship
    enum ship_orientation : bool {
        SO_HOR,       ///< horizontal
        SO_VERT       ///< vertical
    };


    /// result of a hit on a cell
    enum shot_result : uint8_t {
        SR_MISS,      ///< the shot cell was empty
        SR_HIT,       ///< the shot hit a part of a ship
        SR_SINK       ///< the shot sinked a ship (hit the last standing part of the ship)
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
        @brief Check if ship part can be placed on the cell

        @return true if cell is empty, false otherwise
    */
    inline bool can_place(){
        return (state == CS_EMPTY);
    }


    /*!
        @brief Check if the cell can be shot at

        @return true if cell has not been shot at yet, false otherwise
    */
    inline bool can_shoot(){
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

        // maximum number of ships (MODIFY if necessary)
        _max_n_ships({
            {ST_TWO,   1},
            {ST_THREE, 2},
            {ST_FOUR,  1},
            {ST_FIVE,  1}
        }),
        _ready(false)
    {

        // there are no ships at the beginning
        for(auto& tp : _max_n_ships) _n_ships[tp.first] = 0;

        // allocate memory for the cell array
        _data = new cell[_width * _height];

    }


    /// Destructor frees _data
    ~bs_grid(){
        delete[] _data;
    }


    /// Getter for width
    size_t width() const { return _width; }


    /// Getter for height
    size_t height() const { return _height; }


    /// True if all ships have been placed
    bool is_ready() const { return _ready; }


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

        // row-major order
        return _data[row*_width + col];
    }


    /*!
        @brief Ship placement

        Checks provided placement coordinates and places the ship on the board
        if possible

        @param type Type of ship to be placed (example: ST_TWO)
        @param row, col Coordinates of left- and upper-most (!) cell of the ship
        @param orient Orientation of the ship (SO_HOR or SO_VER)
        @return false if its impossible to place the ship at the 
                given configuration, true otherwise
    */
    bool place_ship(ship_type type, size_t row, size_t col, ship_orientation orient){

        // if board is fully populated, there are no more ships to place
        if(_ready)
            throw illegal_move_exception("All ships have already been placed");

        // check if ship type TYPE exists
        if(_n_ships.find(type) == _n_ships.end()){
            throw illegal_move_exception("Unknown ship type");
        }

        // check if maximum # of ships of type type have already been placed
        if(_n_ships[type] == _max_n_ships[type]){
            throw illegal_move_exception("Ship type has been placed MAX times already");
        }

        // holds cells to place ship on if placement is possible
        std::vector<std::pair<size_t, size_t>> to_place;
        size_t r = row, c = col;

        // loop over the ship length
        for(int sz=0; sz<type; ++sz){

            try{
                // if any of the cells are not available, the placement cannot be done
                if(!cell_at(r, c).can_place()) return false;
            }
            catch(index_exception& e){
                // placement is not possible if a coordinate is out of bounds
                return false;
            }

            // if the cell is okay to place, add it to vector
            to_place.push_back({r, c});

            if(orient == SO_HOR) ++c;
            else ++r;
        }

        // place ship
        for(auto& coord : to_place){
            cell_at(coord.first, coord.second).state = CS_FULL;
        }
        
        ++_n_ships[type];

        // check all ships and set _ready
        bool rd = true;
        for(auto& tp : _n_ships)
            rd = rd && (tp.second == _max_n_ships[tp.first]);

        return true;
    }



    /*!
        @brief Shooting

        Checks provided shot coordinates and shoots the cell if possible.
        Throws an index_exception if the coordinates are out of bounds

        @param row, col Coordinates of the cell to be shot at
        @return The result of the shot (one of HT_MISS, HT_HIT, and HT_SINK)
    */
    shot_result shoot_at(size_t row, size_t col){
        
        // the move is illegal if the cell has been shot before
        if(!cell_at(row, col).can_shoot())
            throw illegal_move_exception("Cell has been shot before");

        shot_result sr;

        // change state of the cell depending on previous state
        if(cell_at(row, col).state == CS_EMPTY){
            cell_at(row, col).state = CS_MISSED;
            sr = SR_MISS;
        }
        else if(cell_at(row, col).state == CS_FULL){
            cell_at(row, col).state = CS_DESTROYED;

            // TODO check if the ship has been sunk
        }

        return sr;
    }



    friend std::ostream& operator<<(std::ostream& os, bship::bs_grid& grid);


private:
    size_t                        _width;        ///< width of the grid
    size_t                        _height;       ///< height of the grid
    cell                         *_data;         ///< actual cells of the grid
    std::map<ship_type, uint8_t>  _n_ships;      ///< number of ships of each type
    std::map<ship_type, uint8_t>  _max_n_ships;  ///< maximum number of ships of each type
    bool                          _ready;        ///< true iff all ships have been placed

};




#ifndef SMALL_PRINT

/*!
    @brief Prints the grid

    Overloaded operator << to print the grid to an output stream

    @param os Reference to output stream to print to
    @param grid Reference to a bs_grid object
    @return Reference to the stream
*/
std::ostream& bship::operator<<(std::ostream& os, bship::bs_grid& grid){

    // print first line
    os << "┌─";
    for(size_t i=0; i<grid._width-1; ++i) os << "──┬─";
    os << "──┐" << std::endl;

    // print cells
    for(size_t r=0; r<grid._height; ++r){
        os << "│";
        for(size_t c=0; c<grid._width; ++c){
            switch(grid.cell_at(r, c).state){
                case CS_EMPTY:
                    os << "   ";
                    break;
                case CS_FULL:
                    os << "███";
                    break;
                case CS_MISSED:
                    os << " X ";
                    break;
                case CS_DESTROYED:
                    os << "╬╬╬";
                    break;
            }
            os << "│";
        }
        os << std::endl;

        if(r != grid._height-1){
            // print separating lines if its not the last row
            os << "├─";
            for(size_t i=0; i<grid._width-1; ++i) os << "──┼─";
            os << "──┤" << std::endl;
        }
    }

    // print last line
    os << "└─";
    for(size_t i=0; i<grid._width-1; ++i) os << "──┴─";
    os << "──┘" << std::endl;

    return os;
}

#endif




#ifdef SMALL_PRINT

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
    for(size_t i=0; i<grid._width*3-1; ++i) os << "_";
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
        os << std::endl;
    }

    return os;
}

#endif



#endif