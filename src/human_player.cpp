#include "human_player.h"

namespace bship{


human_player::human_player(std::string& n, bs_grid* hdg, bs_grid* htg, battleship *gm)
:   bs_player(n, hdg, htg, gm)
{}


human_player::human_player(std::string nm)
:   bs_player(nm)
{}


human_player::human_player()
:   bs_player()
{}


void human_player::move(){

    if(game == nullptr || hidden_grid == nullptr || hit_grid == nullptr){
        std::cout << "Can't move on a nullptr {game, hidden_grid, hit_grid}" << std::endl;
        throw illegal_move_exception("Move on nullptr");
    }

    ship_type st;
    int r, c;
    ship_orientation ori;
    std::pair<shot_result, int> sr;
    bool valid_move = false;
    int type, orient;

    if(hidden_grid->is_ready()){
        // placement
        while(!valid_move){
            std::cout << "Enter ship type (length) (2, 3, 4 or 5), coordinates (row, col) and orientation (0: HOR, 1:VERT)\n";
            std::cout << "ex: 2 5 0 1 = 2-cell ship placed vertically at (5, 0)\n";
            std::cout << ">> ";
            std::cin >> type >> r >> c >> orient;
            st = (ship_type) type;
            ori = (ship_orientation) orient;

            try{
                valid_move = game->place_ship(stype[sindex], r, c, ori);
            }
            catch(illegal_move_exception& e){
                std::cout << "Illegal move, try again" << std::endl;
            }
        }
    }
    else{
        // shooting
        while(!valid_move){
            std::cout << "Enter  coordinates (row, col)\n";
            std::cout << "ex: 2 5 = shoot cell (2, 5)\n";
            std::cout << ">> ";
            std::cin >> r >> c;

            try{
                sr = game->shoot_at(r, c);
                valid_move = true;
            }
            catch(illegal_move_exception& e){
                std::cout << "Illegal move, try again" << std::endl;
            }
        }
    }

}


}