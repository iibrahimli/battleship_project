/*!
    A game grid for battleship
*/

#ifndef BS_GRID_HPP
#define BS_GRID_HPP


#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "exceptions.hpp"


// for small printing - comment for ASCII table printing
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


    /// which phase grid is in
    enum grid_state : uint8_t {
        GS_PLACING,   ///< a player is placing ships, not ready yet
        GS_READY      ///< the grid is ready for game (all the ships have been placed)
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
    bs_grid(size_t width_, size_t height_);


    /// Destructor frees data
    ~bs_grid();


    /// Getter for width
    size_t get_width() const;


    /// Getter for height
    size_t get_height() const;


    /// Returns true if all ships have been placed
    bool is_ready() const;


    /// Returns the number of alive ships on the grid
    int get_num_alive_ships() const;


    /// Returns map of ship number per type
    std::map<ship_type, uint8_t> get_n_ships() const;


    /// Returns map of maximum ships per type
    std::map<ship_type, uint8_t> get_max_n_ships() const;


    /*!
        @brief Cell access

        Easy cell access. Throws index_exception if index is out of bounds.
        Cells are stored in row-major order

        @param row, col Coordinates of requested cell
        @return Reference to the requested cell
    */
    cell& cell_at(size_t row, size_t col);


    /*!
        @brief Check whether ship has sunk

        Checks all cells of ship with given id and returns true if all of them have been hit.

        @param ship_id Id of the ship to be checked
        @return true if ship has been sunk, false otherwise
    */
    bool ship_sunk(int ship_id);


    /*!
        @brief Check whether all the ships have been destroyed

        Checks all cells of all ships and returns true if all of them have been hit.

        @return true if all the ships have been sunk, false otherwise
    */
    bool all_ships_sunk();


    /*!
        @brief Ship placement

        Checks provided placement coordinates and places the ship on the board
        if possible. ATTENTION: If the placement of the ship is impossible due to
            1) parts of ship being out of bounds of the grid
            2) parts of ship overlapping with another ship
        no exceptions are thrown and false is returned. This is done to make writing
        bots relying on randomness easier (less overhead during possible move search)

        @param type Type of ship to be placed (example: ST_TWO)
        @param row, col Coordinates of left- and upper-most (!) cell of the ship
        @param orient Orientation of the ship (SO_HOR or SO_VER)
        @return false if its impossible to place the ship at the 
                given configuration, true otherwise
    */
    bool place_ship(ship_type type, size_t row, size_t col, ship_orientation orient);


    /*!
        @brief Shooting

        Checks provided shot coordinates and shoots the cell if possible.
        Throws an index_exception if the coordinates are out of bounds

        @param row, col Coordinates of the cell to be shot at
        @return The result of the shot (one of HT_MISS, HT_HIT, and HT_SINK) and id of ship sunk (if sunk)
    */
    std::pair<shot_result, int> shoot_at(size_t row, size_t col);
    

    friend std::ostream& operator<<(std::ostream& os, bship::bs_grid& grid);


private:

    size_t                        width;        ///< width of the grid
    size_t                        height;       ///< height of the grid
    cell                         *data;         ///< actual cells of the grid
    grid_state                    state;        ///< current state of the grid (related to game phase)
    std::map<ship_type, uint8_t>  n_ships;      ///< number of ships of each type (initialized at runtime)
    std::map<ship_type, uint8_t>  max_n_ships;  ///< maximum number of ships of each type (initialized at runtime)
    int                           alive_ships;  ///< number of alive ships
    int                           cur_ship_id;  ///< id of the ship that is being placed (ids are sequential and start from 0)

};


#endif