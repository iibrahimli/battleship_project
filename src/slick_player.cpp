#include "slick_player.h"

namespace bship{


slick_player::slick_player(std::string& n, bs_grid* hdg, bs_grid* htg, battleship *gm, float difficulty)
:   bs_player(n, hdg, htg, gm),
    peek_prob(difficulty)
{}


slick_player::slick_player(std::string nm, float difficulty)
:   bs_player(nm),
    peek_prob(difficulty)
{}


slick_player::slick_player()
:   bs_player()
{}


void slick_player::move(){

    if(game == nullptr || hidden_grid == nullptr || hit_grid == nullptr){
        std::cout << "Can't move on a nullptr {game, hidden_grid, hit_grid}" << std::endl;
        throw illegal_move_exception("Move on nullptr");
    }

    int r, c;
    std::pair<shot_result, int> sr;
    bool valid_move = false;
    unsigned long tries = 0;
    float prob;
    
    if(stype.size() == 0){
        // add possible ship types to array
        for(auto& p : hidden_grid->get_max_n_ships()){
            for(int i=0; i<p.second; ++i)
                stype.push_back(p.first);
        }
    }
    ship_orientation ori;

    if(!hidden_grid->is_ready()){
        // placement

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
        // shooting

        prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if(prob < peek_prob){
            // guaranteed hit
            bs_grid *opponent_grid = (game->pa_turn) ? &(game->pb_hidden_grid) : &(game->pa_hidden_grid);
            size_t i=0, j=0;

            while(opponent_grid->cell_at(i, j).state != CS_FULL){
                i = rand() % opponent_grid->get_height();
                j = rand() % opponent_grid->get_width();
            }
            
            sr = game->shoot_at(i, j);

            return;
        }

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