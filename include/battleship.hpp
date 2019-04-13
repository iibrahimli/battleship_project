/*!
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

        Constructs a game with grid of given size. A game holds 4 grids.
        All of the grids are of the same size. Each players owns 2 of the grids.
        For each player, one of the grid keeps track of their own ships and opponent's hits,
        while the other grid keeps track of player's hits and sunken enemy ships.
        Starting player becomes player A.

        @param width, height Dimensions of the grid
    */
    battleship(size_t width, size_t height)
    :   pa_hidden_grid(width, height),
        pa_hit_grid   (width, height),
        pb_hidden_grid(width, height),
        pb_hit_grid   (width, height),
        pa_turn(true)
    {

    }



private:
    bs_grid    pa_hidden_grid;  ///< player A ship placement grid
    bs_grid    pa_hit_grid;     ///< player A hit tracking grid
    bs_grid    pb_hidden_grid;  ///< player B ship placement grid
    bs_grid    pb_hit_grid;     ///< player B hit tracking grid
    bs_player  pa;              ///< player A
    bs_player  pb;              ///< player B
    bool       pa_turn;         ///< current turn: player A

};



#endif
