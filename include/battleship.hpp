/*
    Battleship game
*/

#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include "bs_grid.hpp"

namespace bship{
    class battleship;
}


class bship::battleship{
public:
    battleship(size_t width, size_t height)
    :   _grid(width, height)
    {
    }

private:
    bs_grid _grid;

};


#endif
