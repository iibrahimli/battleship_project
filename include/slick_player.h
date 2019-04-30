/*!
    A battleship bot
*/

#ifndef SLICK_PLAYER_HPP
#define SLICK_PLAYER_HPP


#include "battleship.h"
#include "bs_player.h"
#include "exceptions.hpp"


namespace bship{
    class battleship;
    class slick_player;
}



/*!
    @class slick_player

    @brief Slick battleship player

    Takes a peek at the opponent's hidden grid every now and then ;)
    You can run, but you can't hide
*/
class bship::slick_player : public bs_player {
public:

    /*!
        @brief Constructor with grid and game pointers

        Constructs a player with given grids and game. The grids are pointers
        to bs_grid objects inside the relevant game object. Players get
        all game state information through their grids. Players are free
        to keep track of any additional data they deem useful.
        The game is a pointer to the game on which the player makes moves

        @param hdg, htg Hidden and hit grid pointers of the player
        @param gm Pointer to the game
        @param difficulty Difficulty of the bot (from [0, 1], 0 being totally random bot, and 1 being perfect player)
    */
    slick_player(std::string& n, bs_grid* hdg, bs_grid* htg, battleship *gm, float difficulty=0.2);


    /// Name constructor
    slick_player(std::string nm, float difficulty=0.2);


    /// Default constructor initializes everything to nullptr
    slick_player();


    void move();


private:
    float peek_prob = 0.2;   ///< Probability of peeking at opponent's grid ( ∈ [0, 1], since it is a probability )

};


#endif