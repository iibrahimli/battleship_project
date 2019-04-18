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
        ships_placed(false),
        pa_turn(true),
        pa_won(false)
    {
        pa = nullptr;
        pb = nullptr;
    }


    /// Player a getter
    bs_player * get_pa(){ return pa; }


    /// Player b getter
    bs_player * get_pb(){ return pb; }


    /// Player a setter
    void set_pa(bs_player *p){ pa = p; }


    /// Player b setter
    void set_pb(bs_player *p){ pb = p; }


    /// returns the pointer to winner
    bs_player * get_winner(){ return (!finished) ? nullptr : (pa_won) ? pa : pb; }


    /*!
        @brief Place a ship

        Places a ship of current player at the given location
        Arguments are same as bs_grid::place_ship. Does not 
        catch any exceptions thrown by bs_grid::place_ship.
        For more info check documentation of bs_grid::place_ship

        @param type Type of ship to be placed (example: ST_TWO)
        @param row, col Coordinates of left- and upper-most (!) cell of the ship
        @param orient Orientation of the ship (SO_HOR or SO_VER)
        @return false if its impossible to place the ship at the 
                given configuration, true otherwise
    */
    bool place_ship(ship_type type, size_t row, size_t col, ship_orientation orient){
        bool res;

        // place the ship on current player's hidden grid
        // may throw illegal_move_exception
        if(pa_turn){
            res = pa_hidden_grid.place_ship(type, row, col, orient);
            if(pa_hidden_grid.is_ready()) ships_placed = true;
        }
        else{
            res = pb_hidden_grid.place_ship(type, row, col, orient);
            if(pb_hidden_grid.is_ready()) ships_placed = true;
        }

        // go to next turn if this turn was successful
        if(res) pa_turn = !pa_turn;

        return res;
    }


    /*!
        @brief Shoot

        Current player shoots at the given location
        Arguments are same as bs_grid::shoot_at(). Does not
        catch any exceptions thrown by bs_grid::shoot_at()

        @param row, col Coordinates of the cell to be shot at
        @return The result of the shot (one of HT_MISS, HT_HIT, and HT_SINK) and id of ship sunk (if sunk)
    */
    std::pair<shot_result, int> shoot_at(size_t row, size_t col){
        std::pair<shot_result, int> res;
        // instead of doing the same thing in two branches, pointers are kept
        bs_grid *opponent_hidden_grid, *player_hit_grid;

        // set relevant hidden and hit grids (DRY)
        player_hit_grid      = (pa_turn) ? &pa_hit_grid    : &pb_hit_grid;
        opponent_hidden_grid = (pa_turn) ? &pb_hidden_grid : &pa_hidden_grid;

        // may throw index_exception or illegal_move_exception
        res = opponent_hidden_grid->shoot_at(row, col);
        
        // set appropriate state on current player's hit grid based on result
        player_hit_grid->cell_at(row, col).state = (res.first == SR_MISS) ? CS_MISSED : CS_DESTROYED;

        // if the hit ship was the last one
        if(res.first == SR_SINK && opponent_hidden_grid->get_num_alive_ships() == 0){
            finished = true;
        }

        // next player moves if current player misses
        if(res.first == SR_MISS) pa_turn = !pa_turn;

        return res;
    }


    /// Starts the game, i.e. game will call players until game is finished
    void start(){
        while(!finished){
            pa->move();
            if(finished) break;
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
    bool        ships_placed;    ///< all the ships have been placed, game is commenced
    bool        pa_turn;         ///< current turn: player A
    bool        pa_won;          ///< true if player A has won, false otherwise. only relevant if game is finished

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
