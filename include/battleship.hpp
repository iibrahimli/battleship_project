/*
    Battleship game
*/

#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include "bs_grid.hpp"
#include "exceptions.hpp"


namespace bship{
    class battleship;
}

/*!
    @class battleship

    @brief Battleship engine

    The engine of the game, works via an API
*/
class bship::battleship{
public:


    /*!
        @brief Constructor with grid size

        Constructs a game with grid of given size

        @param width, height Dimensions of the grid
    */
    battleship(size_t width, size_t height)
    :   _grid(width, height)
    {
    }

private:
    bs_grid _grid;   ///< game grid

};


#endif
