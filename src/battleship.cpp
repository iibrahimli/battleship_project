#include "battleship.h"

namespace bship{

battleship::battleship(size_t width, size_t height)
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


bs_player * battleship::get_pa(){ return pa; }


bs_player * battleship::get_pb(){ return pb; }


void battleship::set_pa(bs_player *p){ pa = p; }


void battleship::set_pb(bs_player *p){ pb = p; }


bs_player * battleship::get_winner(){ return (!finished) ? nullptr : (pa_won) ? pa : pb; }


bool battleship::place_ship(ship_type type, size_t row, size_t col, ship_orientation orient){
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


std::pair<shot_result, int> battleship::shoot_at(size_t row, size_t col){
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


void battleship::start(){
    while(!finished){
        pa->move();
        if(finished) break;
        pb->move();
    }
}


void connect(battleship *game, bs_player *pa, bs_player *pb){
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


}