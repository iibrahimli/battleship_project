#include <iostream>
#include <string>
#include "battleship.h"
#include "console_game.h"
#include "bs_player.h"
#include "human_player.h"

using namespace bship;
using namespace std;


int main(){
    srand(time(NULL));

    string user_name;
    cout << "Enter your name: ";
    getline(cin, user_name);

    console_game game(10, 10, new human_player(user_name), new bs_player("Random Bot"), OM_PA);
    game.start();
    
    return 0;
}