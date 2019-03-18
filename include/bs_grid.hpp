/*
    A game grid for battleship
*/

#ifndef BS_GRID_HPP
#define BS_GRID_HPP

namespace battleship{
    enum cell_state { EMPTY, FULL, DESTROYED };
    struct cell;
    class bs_grid;
}



// simple cell holding data about itself
// basic element of a grid
struct battleship::cell{
    cell_state state   = EMPTY;
    int        ship_id = -1;
    
};


class battleship::bs_grid{
public:
    bs_grid() = default;

    ~bs_grid(){
        delete[] 
    }

private:
    cell *_data;

};


#endif
