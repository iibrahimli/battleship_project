/*!
    A human battleship player
*/

#ifndef HUMAN_PLAYER_HPP
#define HUMAN_PLAYER_HPP


#include "battleship.h"
#include "bs_player.h"
#include "exceptions.hpp"


namespace bship{
    class battleship;
    class human_player;
}



/*!
    @class human_player

    @brief Human battleship player

    Takes commands from human (terminal input)
*/
class bship::human_player : public bs_player {
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
    */
    human_player(std::string& n, bs_grid* hdg, bs_grid* htg, battleship *gm);


    /// Name constructor
    human_player(std::string nm);


    /// Default constructor initializes everything to nullptr
    human_player();


    void move();


protected:
    

};


#endif