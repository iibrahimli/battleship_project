/*!
    Console launcher for the game
*/

#ifndef CONSOLE_GAME_HPP
#define CONSOLE_GAME_HPP

#include <iostream>
#include "battleship.hpp"
#include "bs_player.hpp"


namespace bship{

    class console_game;


    /*!
        @brief Print 2 grids side by side

        Prints a player's 

        @param g1, g2 Grids to be printed
    */
    void print_grids(bship::bs_grid g1, bship::bs_grid g2); 

}


/*!
    @class bs_player

    @brief Battleship player

    A generic Battleship player interface
*/
class bship::console_game{

public:

    /*!
        @brief Default constructor

        Initializes the game with given players, if one of
        the players is nullptr, that player is initialized
        to random bot

        @param a, b Pointers to player A and player B resp.
    */
    console_game(bs_player *a = nullptr, bs_player *b = nullptr)
    :   pa(a), pb(b)
    {
        game = new battleship(10, 10);
        if(pa == nullptr) pa = new bs_player();
        if(pb == nullptr) pb = new bs_player();
        connect(game, pa, pb);
    }


    /// Destructor deletes the game and players
    ~console_game(){
        delete game;
        delete pa;
        delete pb;
    }


    /// Starts the game
    void start(){
        game->start();

        // the game will handle moves until the end
        std::cout << game->get_winner()->get_name() << " won" << std::endl;
    }


private:

    battleship  *game;   ///< the game engine
    bs_player   *pa;     ///< player A
    bs_player   *pb;     ///< player B

};



void bship::print_grids(bship::bs_grid g1, bship::bs_grid g2){

    // print top numbers
    std::cout << "   ";
    for(size_t i=0; i<g1.get_width()*3-1; ++i){
        if((i+2) % 3 == 0)
            std::cout << i / 3 << " ";
        else
            std::cout << " ";
    }

    // 10 spaces between grids
    std::cout << "          ";
    std::cout << "    ";
    for(size_t i=0; i<g2.get_width()*3-1; ++i){
        if((i+2) % 3 == 0)
            std::cout << i / 3 << " ";
        else
            std::cout << " ";
    }

    std::cout << std::endl;


    // print first line
    std::cout << "  ┌─";
    for(size_t i=0; i<g1.get_width()-1; ++i) std::cout << "──┬─";
    std::cout << "──┐";

    std::cout << "          ";
    std::cout << "  ┌─";
    for(size_t i=0; i<g2.get_width()-1; ++i) std::cout << "──┬─";
    std::cout << "──┐";

    std::cout << std::endl;


    // print cells
    for(size_t r=0; r<g1.get_height(); ++r){
        std::cout << r << " ";
        std::cout << "│";
        for(size_t c=0; c<g1.get_width(); ++c){
            switch(g1.cell_at(r, c).state){
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

        if(r < g2.get_height()){
            std::cout << "          ";
            std::cout << r << " ";
            std::cout << "│";
            for(size_t c=0; c<g2.get_width(); ++c){
                switch(g2.cell_at(r, c).state){
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

        if(r != g1.get_height()-1){
            // print separating lines if its not the last row
            std::cout << "  ├─";
            for(size_t i=0; i<g1.get_width()-1; ++i) std::cout << "──┼─";
            std::cout << "──┤";
            if(r == g2.get_height()-1) 
                std::cout << std::endl;
        }
        
        if(r < g2.get_height()-1){
            std::cout << "          ";
            // print separating lines if its not the last row
            std::cout << "  ├─";
            for(size_t i=0; i<g2.get_width()-1; ++i) std::cout << "──┼─";
            std::cout << "──┤";
            std::cout << std::endl;
        }


    }

    // print last line
    std::cout << "  └─";
    for(size_t i=0; i<g1.get_width()-1; ++i) std::cout << "──┴─";
    std::cout << "──┘";

    std::cout << "          ";
    std::cout << "  └─";
    for(size_t i=0; i<g2.get_width()-1; ++i) std::cout << "──┴─";
    std::cout << "──┘" << std::endl;

}


#endif