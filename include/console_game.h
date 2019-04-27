/*!
    Console launcher for the game
*/

#ifndef CONSOLE_GAME_HPP
#define CONSOLE_GAME_HPP

#include <iostream>
#include "battleship.h"
#include "bs_player.h"


namespace bship{

    class console_game;


    /*!
        @brief Print 2 grids side by side

        Prints a player's 

        @param g1, g2 Grids to be printed
    */
    void print_grids(bship::bs_grid *g1, bship::bs_grid *g2); 

}


/*!
    @class bs_player

    @brief Battleship player

    A generic Battleship player interface
*/
class bship::console_game{

public:

    /*!
        @brief Default constructor

        Initializes the game with given players, if one of
        the players is nullptr, that player is initialized
        to random bot

        @param rows, cols Dimensions of the game
        @param a, b Pointers to player A and player B resp.
    */
    console_game(size_t rows, size_t cols, bs_player *a = nullptr, bs_player *b = nullptr, bool verb=false);


    /// Destructor deletes the game and players
    ~console_game();


    /// Starts the game
    void start();


private:

    battleship  *game;   ///< the game engine
    bs_player   *pa;     ///< player A
    bs_player   *pb;     ///< player B

};





#endif