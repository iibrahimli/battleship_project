#include "bs_player.h"


namespace bship{

bs_player::bs_player(std::string& n, bs_grid* hdg, bs_grid* htg, battleship *gm)
:   name(n),
    hidden_grid(hdg),
    hit_grid(htg),
    game(gm),
    sindex(0)
{}

bs_player::bs_player(std::string nm)
:   name(nm),
    hidden_grid(nullptr),
    hit_grid(nullptr),
    game(nullptr),
    sindex(0)
{}


bs_player::bs_player()
:   name("<Unknown>"),
    hidden_grid(nullptr),
    hit_grid(nullptr),
    game(nullptr),
    sindex(0)
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
        throw illegal_move_exception("Move on nullptr");
    }

    size_t r, c;
    std::pair<shot_result, int> sr;
    bool valid_move = false;
    unsigned long tries = 0;
    ship_orientation ori;
    
    if(stype.size() == 0){
        // add possible ship types to array
        for(auto& p : hidden_grid->get_max_n_ships()){
            for(int i=0; i<p.second; ++i)
                stype.push_back(p.first);
        }
    }

    if(!hidden_grid->is_ready()){
        while(!valid_move){
            ++tries;            
            r = rand() % hit_grid->get_height();
            c = rand() % hit_grid->get_width();
            ori = (rand() % 2) ? SO_HOR : SO_VERT;

            try{
                valid_move = game->place_ship(stype[sindex], r, c, ori);
                if(valid_move) ++sindex;
            }
            catch(illegal_move_exception& e){}
        }
    }
    else{
         while(!valid_move){
            ++tries;
            r = rand() % hit_grid->get_height();
            c = rand() % hit_grid->get_width();

            try{
                sr = game->shoot_at(r, c);
                valid_move = true;
            }
            catch(illegal_move_exception& e){}
        }
    }
}


}