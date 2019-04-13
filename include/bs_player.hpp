/*!
    A battleship player interface
*/

#ifndef BS_PLAYER_HPP
#define BS_PLAYER_HPP


#include "bs_grid.hpp"
#include "battleship.hpp"
#include "exceptions.hpp"


namespace bship{
    class battleship;
    class bs_player;
}



/*!
    @class bs_player

    @brief Battleship player

    A generic Battleship player interface
*/
class bship::bs_player{
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
    bs_player(bs_grid* hdg, bs_grid* htg, battleship *gm)
    :   hidden_grid(hdg),
        hit_grid(htg),
        game(gm)
    {
    }

    bs_player()
    :   hidden_grid(nullptr),
        hit_grid(nullptr),
        game(nullptr)
    {
    }


    /// Hidden grid setter
    void set_hidden_grid(bs_grid *hidden){ hidden_grid = hidden; }


    /// Hit grid setter
    void set_hit_grid(bs_grid *hit){ hit_grid = hit; }


    /// Game setter
    void set_game(battleship *gm){ game = gm; }


    /*!
        @brief Makes a move

        Makes a move on its game pointer. This function is overridden
        in other players (classes derived from this one). By default
        this class will follow a random policy
    */
    virtual void move(){
        // TODO
    }


private:
 
    bs_grid     *hidden_grid;  ///< pointer to ship placement grid
    bs_grid     *hit_grid;     ///< pointer to hit tracking grid
    battleship  *game;         ///< pointer to game

};


#endif