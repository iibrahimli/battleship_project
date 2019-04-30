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
    size_t r, c;
    ship_orientation ori;
    std::pair<shot_result, int> sr;
    bool valid_move = false;
    bool valid = false;
    int type;
    char orient = 'd';

    if(!hidden_grid->is_ready()){
        // placement
        
        while(!valid_move){
            std::cout << "Enter ship type (length) (2, 3, 4 or 5), coordinates (row, col) and\n";
            std::cout << "orientation (h for horizontal, v for vertical)\n";
            std::cout << "ex: 2 5 0 v = 2-cell ship placed vertically at (5, 0)\n";
            std::cout << "ships left to place:\n";
            for(auto& s : hidden_grid->get_n_ships()){
                std::cout << (int) s.first << "-cell : " << (int) hidden_grid->get_max_n_ships()[s.first] - s.second << std::endl;
            }

            std::cout << ">> ";
            std::cin >> type;
            std::cin >> r;
            std::cin >> c;
            std::cin >> orient;
            if(std::cin.eof())
                throw std::runtime_error("Unexpected EOF");
            if(orient == '\n')
                std::cout << std::endl;
            if(hidden_grid->get_max_n_ships().find((ship_type) type) == hidden_grid->get_max_n_ships().end()){
                std::cout << "[!] Unexpected ship type" << std::endl;
                continue;
            }
            if(r >= hidden_grid->get_height() || c >= hidden_grid->get_width()){
                std::cout << "[!] Unexpected indices" << std::endl;
                std::cin.clear();
                std::cin.ignore(100, '\n');
                continue;
            }

            st = (ship_type) type;

            if(orient == 'V' || orient == 'v') ori = SO_VERT;
            else if(orient == 'H' || orient == 'h') ori = SO_HOR;
            else { std::cout << "[!] Invalid orientation" << std::endl; continue; }

            try{
                valid_move = game->place_ship(st, r, c, ori);
                if(!valid_move) std::cout << "[!] Can't place that way" << std::endl;
            }
            catch(illegal_move_exception& e){
                std::cout << "[!] Illegal move, try again" << std::endl;
            }
        }
    }
    else{
        // shooting
        while(!valid_move){
            std::cout << "Enter coordinates (row, col)\n";
            std::cout << "ex: 2 5 = shoot cell (2, 5)\n";
            std::cout << ">> ";
            std::cin >> r;
            std::cin >> c;
            if(std::cin.eof()) throw std::runtime_error("EOF");
            if(r >= hidden_grid->get_height() || c >= hidden_grid->get_width()){
                std::cout << "[!] Unexpected indices" << std::endl;
                std::cin.clear();
                std::cin.ignore(100, '\n');
                continue;
            }

            try{
                sr = game->shoot_at(r, c);
                valid_move = true;
            }
            catch(illegal_move_exception& e){
                std::cout << "[!] Illegal move, try again" << std::endl;
            }
            catch(index_exception& e){
                std::cout << "[!] Index out of bounds, try again" << std::endl;
            }
        }
    }

}


}