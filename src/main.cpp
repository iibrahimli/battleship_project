#include "battleship.h"
#include "bs_player.h"
#include "console_game.h"

using namespace bship;
using namespace std;

int main(){

    srand(time(NULL));
    console_game game(10, 10);
    game.start();
    
    return 0;
}