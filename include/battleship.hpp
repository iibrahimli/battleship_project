/*!
    Battleship game
*/

#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include "bs_grid.hpp"
#include "bs_player.hpp"
#include "exceptions.hpp"


namespace bship{

    class battleship;


    /*!
        @brief Connect game and its players

        Connects given players and the game. If one of the players
        is nullptr, only the other one is connected.

        @param game Pointer to the battleship game
        @param pa, pb Pointers to players A and B
    */
    void connect(battleship *game, bs_player *pa, bs_player *pb);

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
        Starting player becomes player A. Each turn, the game switches between players

        @param width, height Dimensions of the grid
    */
    battleship(size_t width, size_t height)
    :   pa_hidden_grid(width, height),
        pa_hit_grid   (width, height),
        pb_hidden_grid(width, height),
        pb_hit_grid   (width, height),
        finished(false),
        pa_turn(true)
    {
        pa = nullptr;
        pb = nullptr;
    }


    /// Player a setter
    void set_pa(bs_player *p){ pa = p; }


    /// Player b setter
    void set_pb(bs_player *p){ pb = p; }


    /*!
        @brief Place a ship

        Current player places a ship at the given location
        Arguments are same as bs_grid.place_ship()
    */
    bool place_ship()


    /// Starts the game, i.e. game will call players until game is finished
    void start(){
        while(!finished){
            pa->move();
            pb->move();
        }
    }


private:

    bs_grid     pa_hidden_grid;  ///< player A ship placement grid
    bs_grid     pa_hit_grid;     ///< player A hit tracking grid
    bs_grid     pb_hidden_grid;  ///< player B ship placement grid
    bs_grid     pb_hit_grid;     ///< player B hit tracking grid
    bs_player  *pa;              ///< pointer to player A
    bs_player  *pb;              ///< pointer to player B
    bool        finished;        ///< game state
    bool        pa_turn;         ///< current turn: player A

};



void bship::connect(battleship *game, bs_player *pa, bs_player *pb){
    if(!game) return;
    if(pa){
        game->set_pa(pa);
        pa->set_game(game);
    }
    if(pb){
        game->set_pb(pb);
        pb->set_game(game);
    }
}



#endif
