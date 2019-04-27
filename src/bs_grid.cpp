#include "bs_grid.h"

namespace bship{

bs_grid::bs_grid(size_t width_, size_t height_)
:   width(width_),
    height(height_),
    // maximum number of ships (MODIFY if necessary)
    max_n_ships({
        {ST_TWO,   1},
        {ST_THREE, 2},
        {ST_FOUR,  1},
        {ST_FIVE,  1}
    }),
    state(GS_PLACING),
    alive_ships(0)
{

    if(width == 0 || height == 0){
        throw index_exception(width, height, "Invalid size:");
    }

    // there are no ships at the beginning and id 0 will be placed first
    for(auto& tp : max_n_ships) n_ships[tp.first] = 0;
    cur_ship_id = 0;

    // allocate memory for the cell array
    data = new cell[width * height];

}


bs_grid::~bs_grid(){
    delete[] data;
}


size_t bs_grid::get_width() const { return width; }


size_t bs_grid::get_height() const { return height; }


bool bs_grid::is_ready() const { return state == GS_READY; }


int bs_grid::get_num_alive_ships() const { return alive_ships; }


std::map<ship_type, uint8_t> bs_grid::get_n_ships() const { return n_ships; }


std::map<ship_type, uint8_t> bs_grid::get_max_n_ships() const { return max_n_ships; }


inline cell& bs_grid::cell_at(size_t row, size_t col){
    if(row >= height || col >= width)
        throw index_exception(row, col, "Index out of bounds: ");

    // row-major order
    return data[row*width + col];
}


inline bool bs_grid::ship_sunk(int ship_id){
    for(size_t i=0; i<height; ++i){
        for(size_t j=0; j<width; ++j){
            // if there exists at least one cell containing part of ship with given id that has not been destroyed
            if(cell_at(i, j).ship_id == ship_id && cell_at(i, j).state == CS_FULL)
                return false;
        }
    }
    return true;
}


inline bool bs_grid::all_ships_sunk(){
    // check all populated cells, and if any of them is not hit, return false
    for(size_t i=0; i<height; ++i){
        for(size_t j=0; j<width; ++j){
            if(cell_at(i, j).state == CS_FULL)
                return false;
        }
    }

    return true;
}


bool bs_grid::place_ship(ship_type type, size_t row, size_t col, ship_orientation orient){

    // check if ship type TYPE exists
    if(n_ships.find(type) == n_ships.end()){
        throw illegal_move_exception("Unknown ship type");
    }

    // check if maximum # of ships of type type have already been placed
    if(n_ships[type] == max_n_ships[type]){
        throw illegal_move_exception("Ship type has been placed MAX times already");
    }

    // holds cells to place ship on if placement is possible
    std::vector<std::pair<size_t, size_t>> to_place;
    size_t r = row, c = col;

    // loop over the ship length and add cells to vector for later placement
    for(int sz=0; sz<type; ++sz){

        try{
            // if any of the cells are not available, the placement cannot be done
            if(!cell_at(r, c).can_place()) return false;
        }
        catch(index_exception& e){
            // placement is not possible if a coordinate is out of bounds
            return false;
        }

        // if the cell is okay to place, add it to vector
        to_place.push_back({r, c});

        // increment column or row value according to orientation
        if(orient == SO_HOR) ++c;
        else ++r;
    }

    // place ship
    for(auto& coord : to_place){
        cell_at(coord.first, coord.second).state = CS_FULL;
        cell_at(coord.first, coord.second).ship_id = cur_ship_id;
    }
    
    // there is one more ship of type TYPE now
    ++n_ships[type];
    ++alive_ships;

    // next id
    ++cur_ship_id;

    // check all ships and set state to ready if all ships are placed
    bool rd = true;
    for(auto& tp : n_ships)
        rd = rd && (tp.second == max_n_ships[tp.first]);
    if(rd) state = GS_READY;

    return true;
}


std::pair<shot_result, int> bs_grid::shoot_at(size_t row, size_t col){
    
    // the move is illegal if the cell has been shot before
    // cell_at() may also throw index_exception
    if(!cell_at(row, col).can_shoot())
        throw illegal_move_exception("Cell has been shot before");

    shot_result sr;
    int shot_ship_id = -1;

    // change state of the cell depending on previous state
    if(cell_at(row, col).state == CS_EMPTY){
        cell_at(row, col).state = CS_MISSED;
        sr = SR_MISS;
    }
    else if(cell_at(row, col).state == CS_FULL){
        cell_at(row, col).state = CS_DESTROYED;
        sr = SR_HIT;
        shot_ship_id = cell_at(row, col).ship_id;

        // if ship is sunk
        if(ship_sunk(shot_ship_id)){
            sr = SR_SINK;
            --alive_ships;
        }
    }

    return {sr, shot_ship_id};
}



#ifndef SMALL_PRINT

/*!
    @brief Prints the grid

    Overloaded operator << to print the grid to an output stream

    @param os Reference to output stream to print to
    @param grid Reference to a bs_grid object
    @return Reference to the stream
*/
std::ostream& bship::operator<<(std::ostream& os, bship::bs_grid& grid){

    // print top numbers
    os << "   ";
    for(size_t i=0; i<grid.width*3-1; ++i){
        if((i+2) % 3 == 0)
            os << i / 3 << " ";
        else
            os << " ";
    }
    os << std::endl;

    // print first line
    os << "  ┌─";
    for(size_t i=0; i<grid.width-1; ++i) os << "──┬─";
    os << "──┐" << std::endl;

    // print cells
    for(size_t r=0; r<grid.height; ++r){
        os << r << " ";
        os << "│";
        for(size_t c=0; c<grid.width; ++c){
            switch(grid.cell_at(r, c).state){
                case CS_EMPTY:
                    os << "   ";
                    break;
                case CS_FULL:
                    os << "███";
                    break;
                case CS_MISSED:
                    os << " X ";
                    break;
                case CS_DESTROYED:
                    os << "╬╬╬";
                    break;
            }
            os << "│";
        }
        os << std::endl;

        if(r != grid.height-1){
            // print separating lines if its not the last row
            os << "  ├─";
            for(size_t i=0; i<grid.width-1; ++i) os << "──┼─";
            os << "──┤" << std::endl;
        }
    }

    // print last line
    os << "  └─";
    for(size_t i=0; i<grid.width-1; ++i) os << "──┴─";
    os << "──┘" << std::endl;

    return os;
}

#endif



#ifdef SMALL_PRINT

/*!
    @brief Prints the grid

    Overloaded operator << to print the grid to an output stream

    @param os Reference to output stream to print to
    @param grid Reference to a bs_grid object
    @return Reference to the stream
*/
std::ostream& operator<<(std::ostream& os, bship::bs_grid& grid){

    // print top numbers
    os << "  ";
    for(size_t i=0; i<grid.width*3-1; ++i){
        if((i+2) % 3 == 0)
            os << i / 3;
        else
            os << " ";
    }
    os << std::endl;

    // print top line
    os << "   ";
    for(size_t i=0; i<grid.width*3-1; ++i) os << "_";
    os << std::endl;

    // print cells
    for(size_t r=0; r<grid.height; ++r){
        os << r << " ";
        os << "|";
        for(size_t c=0; c<grid.width; ++c){
            switch(grid.cell_at(r, c).state){
                case CS_EMPTY:
                    os << "__";
                    break;
                case CS_FULL:
                    // os << "██";
                    os << "_" << grid.cell_at(r, c).ship_id;
                    break;
                case CS_MISSED:
                    os << "×_";
                    break;
                case CS_DESTROYED:
                    // os << "░░";
                    os << "╬╬";
                    break;
            }
            os << "|";
        }
        os << std::endl;
    }

    return os;
}

#endif


}