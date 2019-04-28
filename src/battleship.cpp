#include "battleship.h"
#include "console_game.h"

namespace bship{



battleship::battleship(size_t width, size_t height, output_mode om)
:   pa_hidden_grid(width, height),
    pa_hit_grid   (width, height),
    pb_hidden_grid(width, height),
    pb_hit_grid   (width, height),
    total_shots(0),
    finished(false),
    ships_placed(false),
    pa_turn(true),
    pa_won(false),
    output(om)
{
    pa = nullptr;
    pb = nullptr;
}


bs_player * battleship::get_pa(){ return pa; }


bs_player * battleship::get_pb(){ return pb; }


void battleship::set_pa(bs_player *p){ pa = p; }


void battleship::set_pb(bs_player *p){ pb = p; }


bs_player * battleship::get_winner(){ return (!finished) ? nullptr : (pa_won) ? pa : pb; }


int battleship::get_total_shots(){ return total_shots; }


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
    if(res){
        if(output == OM_BOTH || output == OM_TXTONLY){
            std::string pl = (pa_turn) ? pa->get_name() : pb->get_name();
            std::cout << pl << " placed a " << (int) type << "-cell ship at (" << row << ", " << col << ") ";
            std::cout << ((orient == SO_HOR) ? "horizontally" : "vertically");
            std::cout << std::endl;
        }
        pa_turn = !pa_turn;
    }
    else{
        if(output == OM_BOTH || output == OM_TXTONLY){
            std::string pl = (pa_turn) ? pa->get_name() : pb->get_name();
            std::cout << pl << " tried to place a " << (int) type << "-cell ship at (" << row << ", " << col << ") ";
            std::cout << ((orient == SO_HOR) ? "horizontally" : "vertically");
            std::cout << std::endl;
        }
    }

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
        if(pa_turn) pa_won = true;
    }

    // next player moves if current player misses
    if(res.first == SR_MISS) pa_turn = !pa_turn;

    if(output == OM_BOTH || output == OM_TXTONLY){
        std::string pl = (pa_turn) ? pa->get_name() : pb->get_name();
        std::cout << pl << " shot cell (" << row << ", " << col << "): ";
        if(res.first == SR_MISS) std::cout << "MISS";
        else if(res.first == SR_HIT) std::cout << "HIT [" << res.second << "]";
        else std::cout << "SANK [" << res.second << "]";
        std::cout << std::endl;
    }

    ++total_shots;

    return res;
}


void battleship::start(){
    while(!finished){
        std::system("clear");
        if(pa_turn){
            if(output != OM_TXTONLY && (output == OM_BOTH || output == OM_PA)){
                std::cout << pa->get_name() << "'s grids:" << std::endl;
                print_grids(&pa_hidden_grid, &pa_hit_grid);
            }
            pa->move();
        }
        else{
            if(output != OM_TXTONLY && (output == OM_BOTH || output == OM_PB)){
                std::cout << pb->get_name() << "'s grids:" << std::endl;
                print_grids(&pb_hidden_grid, &pb_hit_grid);
            }
            pb->move();
        }
    }
}


void connect(battleship *gm, bs_player *pa, bs_player *pb){
    if(!gm) return;
    if(pa){
        gm->set_pa(pa);
        pa->set_game(gm);
        pa->set_hidden_grid(&(gm->pa_hidden_grid));
        pa->set_hit_grid(&(gm->pa_hit_grid));
    }
    if(pb){
        gm->set_pb(pb);
        pb->set_game(gm);
        pb->set_hidden_grid(&(gm->pb_hidden_grid));
        pb->set_hit_grid(&(gm->pb_hit_grid));
    }
}


}