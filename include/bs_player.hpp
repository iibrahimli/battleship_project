/*!
    A battleship player interface
*/

#ifndef BS_PLAYER_HPP
#define BS_PLAYER_HPP


#include "bs_grid.hpp"
#include "battleship.hpp"
#include "exceptions.hpp"


namespace bship{
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
        @brief Constructor with grid references

        Constructs a player with given grids. The grids are references
        to bs_grid objects inside the relevant game object. Players get
        all game state information through their grids. Players are free
        to keep track of any additional data they deem useful

        @param hdg, htg Hidden and hit grid references of the player
    */
    bs_player(bs_grid& hdg, bs_grid& htg)
    :   hidden_grid(hdg),
        hit_grid(htg)
    {   
    }

    bs_player()
    :   hidden_grid()


    void set_hidden_grid();



private:
    bs_grid&  hidden_grid;  ///< ship placement grid
    bs_grid&  hit_grid;     ///< hit tracking grid

};


#endif