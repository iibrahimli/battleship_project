#include "console_game.h"

namespace bship{

console_game::console_game(size_t rows, size_t cols, bs_player *a, bs_player *b, output_mode om)
:   pa(a), pb(b)
{
    game = new battleship(10, 10, om);
    if(pa == nullptr) pa = new bs_player("player A");
    if(pb == nullptr) pb = new bs_player("player B");
    connect(game, pa, pb);
}


console_game::~console_game(){
    delete game;
    delete pa;
    delete pb;
}


void console_game::start(){
    game->start();

    // the game will handle moves until the end
    std::cout << game->get_winner()->get_name() << " won" << std::endl;
    std::cout << "total shots: " << game->get_total_shots() << std::endl;
}



void print_grids(bship::bs_grid *g1, bship::bs_grid *g2){

    // print top numbers
    std::cout << "   ";
    for(size_t i=0; i<g1->get_width()*3-1; ++i){
        if((i+2) % 3 == 0)
            std::cout << i / 3 << " ";
        else
            std::cout << " ";
    }

    // 10 spaces between grids
    std::cout << "          ";
    std::cout << "    ";
    for(size_t i=0; i<g2->get_width()*3-1; ++i){
        if((i+2) % 3 == 0)
            std::cout << i / 3 << " ";
        else
            std::cout << " ";
    }

    std::cout << std::endl;


    // print first line
    std::cout << "  ┌─";
    for(size_t i=0; i<g1->get_width()-1; ++i) std::cout << "──┬─";
    std::cout << "──┐";

    std::cout << "          ";
    std::cout << "  ┌─";
    for(size_t i=0; i<g2->get_width()-1; ++i) std::cout << "──┬─";
    std::cout << "──┐";

    std::cout << std::endl;


    // print cells
    for(size_t r=0; r<g1->get_height(); ++r){
        std::cout << r << " ";
        std::cout << "│";
        for(size_t c=0; c<g1->get_width(); ++c){
            switch(g1->cell_at(r, c).state){
                case bship::CS_EMPTY:
                    std::cout << "   ";
                    break;
                case bship::CS_FULL:
                    std::cout << "███";
                    break;
                case bship::CS_MISSED:
                    std::cout << " X ";
                    break;
                case bship::CS_DESTROYED:
                    std::cout << "╬╬╬";
                    break;
            }
            std::cout << "│";
        }

        if(r < g2->get_height()){
            std::cout << "          ";
            std::cout << r << " ";
            std::cout << "│";
            for(size_t c=0; c<g2->get_width(); ++c){
                switch(g2->cell_at(r, c).state){
                    case bship::CS_EMPTY:
                        std::cout << "   ";
                        break;
                    case bship::CS_FULL:
                        std::cout << "███";
                        break;
                    case bship::CS_MISSED:
                        std::cout << " X ";
                        break;
                    case bship::CS_DESTROYED:
                        std::cout << "╬╬╬";
                        break;
                }
                std::cout << "│";
            }
        }

        std::cout << std::endl;

        if(r != g1->get_height()-1){
            // print separating lines if its not the last row
            std::cout << "  ├─";
            for(size_t i=0; i<g1->get_width()-1; ++i) std::cout << "──┼─";
            std::cout << "──┤";
            if(r == g2->get_height()-1) 
                std::cout << std::endl;
        }
        
        if(r < g2->get_height()-1){
            std::cout << "          ";
            // print separating lines if its not the last row
            std::cout << "  ├─";
            for(size_t i=0; i<g2->get_width()-1; ++i) std::cout << "──┼─";
            std::cout << "──┤";
            std::cout << std::endl;
        }


    }

    // print last line
    std::cout << "  └─";
    for(size_t i=0; i<g1->get_width()-1; ++i) std::cout << "──┴─";
    std::cout << "──┘";

    std::cout << "          ";
    std::cout << "  └─";
    for(size_t i=0; i<g2->get_width()-1; ++i) std::cout << "──┴─";
    std::cout << "──┘" << std::endl;

}

}