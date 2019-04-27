#include "bs_player.h"


namespace bship{

bs_player::bs_player(std::string& n, bs_grid* hdg, bs_grid* htg, battleship *gm)
:   name(n),
    hidden_grid(hdg),
    hit_grid(htg),
    game(gm)
{}


bs_player::bs_player()
:   name("<Unknown>"),
    hidden_grid(nullptr),
    hit_grid(nullptr),
    game(nullptr)
{}


bs_player::~bs_player() = default;


std::string bs_player::get_name(){ return name; }


void bs_player::set_name(std::string& n){ name = n; }


void bs_player::set_hidden_grid(bs_grid *hidden){ hidden_grid = hidden; }


void bs_player::set_hit_grid(bs_grid *hit){ hit_grid = hit; }


void bs_player::set_game(battleship *gm){ game = gm; }


void bs_player::move(){

    if(game == nullptr || hidden_grid == nullptr || hit_grid == nullptr){
        std::cout << "Can't move on a nullptr {game, hidden_grid, hit_grid}" << std::endl;
        return;
    }

    int r, c;
    std::pair<shot_result, int> sr;
    bool valid_move = false;
    static std::vector<ship_type> stype;
    static int sindex = 0;
    if(stype.size() == 0){
        // add possible ship types to array
        for(auto& p : hidden_grid->get_max_n_ships()){
            for(int i=0; i<p.second; ++i)
                stype.push_back(p.first);
        }
    }
    ship_orientation ori;

    if(hidden_grid->is_ready()){
        while(!valid_move){
            r = rand() % hit_grid->get_height();
            c = rand() % hit_grid->get_width();

            try{
                sr = game->shoot_at(r, c);
                valid_move = true;
            }
            catch(illegal_move_exception& e){}
        }
    }
    else{
        while(!valid_move){
            r = rand() % hit_grid->get_height();
            c = rand() % hit_grid->get_width();
            ori = (rand() % 2) ? SO_HOR : SO_VERT;                

            try{
                // TODO
                valid_move = game->place_ship(stype[sindex], r, c, ori);
                ++sindex;
            }
            catch(illegal_move_exception& e){}
        }
    }
}


}