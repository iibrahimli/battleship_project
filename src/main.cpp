#include "battleship.hpp"

using namespace bship;
using namespace std;

int main(){

    bs_grid grid(10, 10);

    grid.cell_at(0, 0).state = CS_MISSED;
    grid.cell_at(1, 0).state = CS_MISSED;
    grid.cell_at(3, 3).state = CS_MISSED;
    
    grid.cell_at(5, 3).state = CS_FULL;
    grid.cell_at(5, 4).state = CS_DESTROYED;
    grid.cell_at(5, 5).state = CS_FULL;
    grid.cell_at(5, 6).state = CS_FULL;

    grid.cell_at(7, 9).state = CS_FULL;
    grid.cell_at(8, 9).state = CS_FULL;
    grid.cell_at(9, 9).state = CS_FULL;

    cout << grid;

    return 0;
}