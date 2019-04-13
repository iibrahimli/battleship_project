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

    The engine of a battleship game between 2 players (Player A and Player B)
*/
class bship::battleship{
public:


    /*!
        @brief Constructor with grid size

        Constructs a game with grid of given size

        @param width, height Dimensions of the grid
    */
    battleship(size_t width, size_t height)
    :   pa_hidden_grid(width, height),
        pa_hit_grid(width, height),
        pb_hidden_grid(width, height),
        pb_hit_grid(width, height)
    {
        
    }



private:
    bs_grid pa_hidden_grid;  ///< player a ship placement grid
    bs_grid pa_hit_grid;     ///< player a hit tracking grid
    bs_grid pb_hidden_grid;  ///< player b ship placement grid
    bs_grid pb_hit_grid;     ///< player b hit tracking grid
    bool p1_turn;            ///< current turn: player 1

};



#endif
