#include "battleship.h"
#include "console_game.h"
#include "human_player.h"

using namespace bship;
using namespace std;


int main(){

    srand(time(NULL));
    console_game game(10, 10, new human_player("Imran"), nullptr, OM_PA);
    game.start();
    
    return 0;
}